// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/BoxComponent.h"
#include "Engine/GameInstance.h"
#include "TP_ThirdPersonCharacter.generated.h"


UCLASS(config=Game)
class ATP_ThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BP_Weapon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BP_Backpack;

public:
	ATP_ThirdPersonCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing= OnRep_CurrentAimState, Category = AnimationParameters)
	bool bIsAimingState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* MyArrowComponent;
	
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
	
	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> character_meshes;
	int current_mesh_id = 0;
	
protected:

	USkeletalMeshComponent* CharacterMeshComponent;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentSkeletalMesh)
	USkeletalMesh* CurrentSkeletalMesh;
	
	void SwitchCharacterRight();

	void SwitchCharacterLeft();

	// Replication function for the CurrentSkeletalMesh variable
	UFUNCTION()
	void OnRep_CurrentSkeletalMesh();

	UFUNCTION(Server, Reliable)
	void SwitchCharacter_Server(USkeletalMesh* NewMesh);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void SwitchCharacter_Multicast(USkeletalMesh* NewMesh);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<class  ABulletActor> BulletClass;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE class UArrowComponent* GetShootArrow() const { return MyArrowComponent; }

	
};

