// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "Animation/AnimInstance.h"
#include "UI/GenericHUD.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEPROJECT2_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
			class USpringArmComponent *SpringArm;
		UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
			class UCameraComponent *Camera;
		UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
			class USkeletalMeshComponent *FP_Mesh;
		UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
			class USkeletalMeshComponent *GunMesh;
public:
	APlayerCharacter();

	UFUNCTION(BlueprintPure, Category = "Character|Gun|Ammo")
		int32 GetCurrentAmmo() const { return CurrentAmmo; }
	UFUNCTION(BlueprintPure, Category = "Character|Gun|Ammo")
		int32 GetMaxAmmo() const { return MaxAmmo; }
	UFUNCTION(BlueprintCallable, Category = "Character|Gun|Ammo")
		void SetCurrentAmmo(int NewAmmo) { CurrentAmmo = NewAmmo; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Camera")
		float BaseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Camera")
		float BaseLookUprate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
		float SprintSpeed;
	UFUNCTION(BlueprintCallable, Category = "Character|Input")
		void PauseGame();
	UFUNCTION(BlueprintCallable, Category = "Character|Input")
		void UnPauseGame();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;
	virtual void OnDeath_Implementation() override;
	virtual void PossessedBy(AController *NewController) override;

	virtual float TakeDamage(
		float DamageAmount, struct FDamageEvent const &DamageEvent,
		class AController *EventInstigator, AActor * DamageCauser)override;

	bool HasAmmo() const { return (CurrentAmmo > 0); }

	UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = "Character|Gun")
		bool bCanShoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Gun|Ammo")
		bool bUnlimitedAmmo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Gun|Ammo")
		int MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Camera")
		float CameraPitchMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Camera")
		float CameraPitchMax;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Gun")
		class UParticleSystem *TrailEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Gun")
		class UParticleSystem *HitEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Gun")
		class UAnimMontage *FireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Gun")
		float DamageAmount;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Input|Movement")
		void OnSprintStart();
	void OnSprintStart_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Input|Movement")
		void OnSprintEnd();
	void OnSprintEnd_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Input|Gun")
		void OnFire();
	virtual void OnFire_Implementation();
	UFUNCTION(BlueprintCallable, Category = "Character|Input|Movement")
		void MoveForward(float Scalar);
	UFUNCTION(BlueprintCallable, Category = "Character|Input|Movement")
		void MoveRight(float Scalar);
	UFUNCTION(BlueprintCallable, Category = "Character|Input|Camera")
		void LookUpAtRate(float Rate);
	UFUNCTION(BlueprintCallable, Category = "Character|Input|Camera")
		void TurnAtRate(float Rate);
	
	int CurrentAmmo;

private:
	float PreviousWalkSpeed;
	void SpawnShootingParticles(FVector ParticleLocation);

	UPROPERTY()
		class AGenericHUD *HudReference;
};
