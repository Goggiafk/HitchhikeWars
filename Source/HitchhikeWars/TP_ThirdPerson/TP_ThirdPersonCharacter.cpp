// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "HitchhikeWars/BulletActor.h"
#include "HitchhikeWars/Gamemanager.h"
#include "HitchhikeWars/MyGamePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


//////////////////////////////////////////////////////////////////////////
// ATP_ThirdPersonCharacter

ATP_ThirdPersonCharacter::ATP_ThirdPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(10.0f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 900.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	MyArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MyArrowComponent"));
	MyArrowComponent->SetupAttachment(RootComponent);
	MyArrowComponent->ArrowSize = 2.0f;
	MyArrowComponent->ArrowColor = FColor::Red; 
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	CurrentSkeletalMesh = GetMesh()->GetSkeletalMeshAsset();
}

void ATP_ThirdPersonCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//UInventoryComponent* InventoryComponent = ;

	if(Cast<AMyGamePlayerController>(GetLocalViewingPlayerController())->InventoryComponent)
	{
		UInventoryItem* TestItem = NewObject<UInventoryItem>();
		TestItem->Name = "Sex2";
		TestItem->Quantity = 1;
		Cast<AMyGamePlayerController>(GetLocalViewingPlayerController())->InventoryComponent->AddItem(TestItem);
	}
	
	USkeletalMeshComponent* MeshComponent = GetMesh();
	if(!MeshComponent)
	{
		return;
	}
	CharacterMeshComponent = GetMesh();

	if(CharacterMeshComponent)
	{
		CharacterMeshComponent->SetSkeletalMesh(character_meshes[current_mesh_id]);
	}

	FTransform WeaponSocketTransform = MeshComponent->GetSocketTransform(TEXT("hand_r_Weapon_Socket"));
	FTransform BackpackSocketTransform = MeshComponent->GetSocketTransform(TEXT("spine_Backpack_Socket"));

	AActor* SpawnedWeapon = GetWorld()->SpawnActor<AActor>(BP_Weapon, WeaponSocketTransform);
	AActor* SpawnedBackpack = GetWorld()->SpawnActor<AActor>(BP_Backpack, BackpackSocketTransform);
	
	if(SpawnedWeapon)
	{
		SpawnedWeapon->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_r_Weapon_Socket"));
		SpawnedBackpack->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("spine_Backpack_Socket"));
	}
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (WidgetClass)
	{
		WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if (WidgetInstance)
		{
			WidgetInstance->AddToViewport();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATP_ThirdPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATP_ThirdPersonCharacter::Move);

		//Aiming
		InputComponent->BindAction("Aim", IE_Pressed, this, &ATP_ThirdPersonCharacter::Aim);
		InputComponent->BindAction("Aim", IE_Released, this, &ATP_ThirdPersonCharacter::StopAim);
		
		InputComponent->BindAction("Shoot", IE_Pressed, this, &ATP_ThirdPersonCharacter::Shoot);
		InputComponent->BindAction("SwitchCharacterRight", IE_Pressed, this, &ATP_ThirdPersonCharacter::SwitchCharacterRight);
		InputComponent->BindAction("SwitchCharacterLeft", IE_Pressed, this, &ATP_ThirdPersonCharacter::SwitchCharacterLeft);
		
	}

}

void ATP_ThirdPersonCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate the CurrentSkeletalMesh variable
	DOREPLIFETIME(ATP_ThirdPersonCharacter, CurrentSkeletalMesh);
}

void ATP_ThirdPersonCharacter::OnRep_CurrentSkeletalMesh()
{
	if (CurrentSkeletalMesh)
	{
		GetMesh()->SetSkeletalMesh(CurrentSkeletalMesh);
	}
}


void ATP_ThirdPersonCharacter::SwitchCharacterRight()
{
	
	if(CharacterMeshComponent)
	{
		current_mesh_id++;
		if(current_mesh_id >= character_meshes.Num())
		{
			current_mesh_id = 0;
		}
		//CharacterMeshComponent->SetSkeletalMesh(character_meshes[current_mesh_id]);
		SwitchCharacter_Server(character_meshes[current_mesh_id]);
	}
	
}

void ATP_ThirdPersonCharacter::SwitchCharacterLeft()
{
	if(CharacterMeshComponent)
	{
		current_mesh_id--;
		if(current_mesh_id < 0)
		{
			current_mesh_id = character_meshes.Num()-1;
		}
	}
	//CharacterMeshComponent->SetSkeletalMesh(character_meshes[current_mesh_id]);
	SwitchCharacter_Server(character_meshes[current_mesh_id]);
}


void ATP_ThirdPersonCharacter::SwitchCharacter_Server_Implementation(USkeletalMesh* NewMesh)
{
	SwitchCharacter_Multicast(NewMesh);
}


void ATP_ThirdPersonCharacter::SwitchCharacter_Multicast_Implementation(USkeletalMesh* NewMesh)
{
	CurrentSkeletalMesh = NewMesh;

	OnRep_CurrentSkeletalMesh();
}

bool ATP_ThirdPersonCharacter::SwitchCharacter_Multicast_Validate(USkeletalMesh* NewMesh)
{
	return true;
}

void ATP_ThirdPersonCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATP_ThirdPersonCharacter::Shoot()
{
	if(bIsAimingState && BulletClass)
	{
		Shoot_Server();
	}
}

void ATP_ThirdPersonCharacter::Shoot_Server_Implementation()
{
	Shoot_Multicast();
}

void ATP_ThirdPersonCharacter::Shoot_Multicast_Implementation()
{
	FTransform ArrowTransform;
	if(MyArrowComponent)
	{
		ArrowTransform = GetShootArrow()->GetComponentTransform();
	}

	ABulletActor* Bullet = GetWorld()->SpawnActor<ABulletActor>(BulletClass, ArrowTransform);

	if(Bullet)
	{
		//FVector ThrowDirection = GetShootArrow()->GetForwardVector();

		//Bullet->ProjectileMovement->Velocity = ThrowDirection * Bullet->ProjectileMovement->InitialSpeed;
	}
}

void ATP_ThirdPersonCharacter::Aim()
{
	Aim_Server(true);
}


void ATP_ThirdPersonCharacter::StopAim()
{
	Aim_Server(false);
}


void ATP_ThirdPersonCharacter::Aim_Server_Implementation(bool state)
{
	Aim_Multicast(state);
}

void ATP_ThirdPersonCharacter::Aim_Multicast_Implementation(bool state)
{
	OnRep_CurrentAimState(state);
}

void ATP_ThirdPersonCharacter::OnRep_CurrentAimState(bool state)
{
	bIsAimingState = state;
}



