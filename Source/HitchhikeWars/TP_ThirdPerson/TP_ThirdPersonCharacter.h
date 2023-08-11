
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "TP_ThirdPersonCharacter.generated.h"

UCLASS(config=Game)
class ATP_ThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATP_ThirdPersonCharacter();

	// Camera Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Input Mapping
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	// Weapon and Backpack Classes
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BP_Weapon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BP_Backpack;

	// Character Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CurrentAimState, Category = AnimationParameters)
	bool bIsAimingState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* MyArrowComponent;

	// Character Functions
	void Aim();
	void StopAim();
	UFUNCTION(Server, Reliable)
	void Aim_Server(bool state);
	UFUNCTION(NetMulticast, Reliable)
	void Aim_Multicast(bool state);

	UFUNCTION()
	void OnRep_CurrentAimState(bool state);

	void Shoot();
	UFUNCTION(Server, Reliable)
	void Shoot_Server();
	UFUNCTION(NetMulticast, Reliable)
	void Shoot_Multicast();

	// Character Meshes and Switching
	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> character_meshes;
	int current_mesh_id = 0;

protected:
	USkeletalMeshComponent* CharacterMeshComponent;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentSkeletalMesh)
	USkeletalMesh* CurrentSkeletalMesh;

	// Character Mesh Switching Functions
	void SwitchCharacterRight();
	void SwitchCharacterLeft();
	UFUNCTION()
	void OnRep_CurrentSkeletalMesh();
	UFUNCTION(Server, Reliable)
	void SwitchCharacter_Server(USkeletalMesh* NewMesh);
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void SwitchCharacter_Multicast(USkeletalMesh* NewMesh);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Input Handling and Widget
	void Move(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<class ABulletActor> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WidgetClass;

	UUserWidget* WidgetInstance;

public:
	// Getter functions
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UArrowComponent* GetShootArrow() const { return MyArrowComponent; }
};
