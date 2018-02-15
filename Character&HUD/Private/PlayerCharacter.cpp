// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (SpringArm)
	{
		SpringArm->SetupAttachment(GetCapsuleComponent());
		SpringArm->RelativeLocation = FVector(-20.0f, 0.0f, 40.0f);
		SpringArm->TargetArmLength = 0.0f;
		SpringArm->bDoCollisionTest = false;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera)
	{
		Camera->FieldOfView = 90.0f;
		Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	}

	FP_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Mesh"));
	if (FP_Mesh)
	{
		FP_Mesh->SetupAttachment(Camera);
	}

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	if (GunMesh)
	{
		GunMesh->SetupAttachment(Camera);
	}

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

	bCanShoot = true;
	bUnlimitedAmmo = false;
	MaxAmmo = 10;
	CurrentAmmo = MaxAmmo;

	BaseTurnRate = 100.0f;
	BaseLookUprate = 100.0f;
	CameraPitchMin = -89.0f;
	CameraPitchMax = 89.0f;

	SprintSpeed = 1500.0f;

	DamageAmount = 10.0f;
	FireAnimation = nullptr;

	TrailEffect = nullptr;
	HitEffect = nullptr;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GunMesh->AttachToComponent(FP_Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("GripPoint"));

	if (CurrentAmmo != MaxAmmo)
	{
		CurrentAmmo = MaxAmmo;
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::OnSprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::OnSprintEnd);

	PlayerInputComponent->BindAxis("Turn",this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::OnFire);
}

void APlayerCharacter::OnDeath_Implementation()
{
	
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentHealth <= 0.0f)
	{
		return 0.0f;
	}

	const float SubstractedHealth = CurrentHealth - DamageAmount;

	if (FMath::IsNearlyZero(SubstractedHealth) || SubstractedHealth < 0.0f)
	{
		CurrentHealth = 0.0f;
		OnDeath();
	}
	else
	{
		CurrentHealth = SubstractedHealth;
	}

	return CurrentHealth;
}

void APlayerCharacter::OnSprintStart_Implementation()
{
	bIsSprinting = true;
	bCanShoot = false;
	PreviousWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

}

void APlayerCharacter::OnSprintEnd_Implementation()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = PreviousWalkSpeed;
	bCanShoot = true;
}

void APlayerCharacter::OnFire_Implementation()
{
	if (bCanShoot)
	{
		if (!HasAmmo() && !bUnlimitedAmmo)
		{
			return;
		}
	}
	else
	{
		return;
	}
	
	{
		FVector ParticleLocation = FVector::ZeroVector;

		{
			//value for invisible ray
			FHitResult Hit;
			const FVector StartTrace = Camera->GetComponentLocation();
			const FVector EndTrace = StartTrace + (Camera->GetForwardVector() * 10000.0f);

			//collision to ignore
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(GetOwner());
			QueryParams.AddIgnoredActor(this);

			//invisible ray
			GetWorld()->LineTraceSingleByChannel(
				Hit, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility, QueryParams);

			//if we hit something, damage it and sst particle location
			if (Hit.bBlockingHit && Hit.GetActor())
			{
				ParticleLocation = Hit.ImpactPoint;
				
				//create general object type
				TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
				
				//set general damage to PointDamage
				FPointDamageEvent PointDamageEvent(DamageAmount, Hit, Hit.ImpactNormal, ValidDamageTypeClass);

				//DamageActor
				Hit.GetActor()->TakeDamage(DamageAmount, PointDamageEvent, GetController(), GetOwner());
			}
			else
			{
				ParticleLocation = EndTrace;
			}
		}
		SpawnShootingParticles(ParticleLocation);
	}

	if (FireAnimation)
	{
		if (UAnimInstance *AnimInstance = FP_Mesh->GetAnimInstance())
		{
			AnimInstance->Montage_Play(FireAnimation);
		}
	}

	if (!bUnlimitedAmmo)
	{
		CurrentAmmo--;
	}

}

void APlayerCharacter::MoveForward(float Scalar)
{
	if (Scalar != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Scalar);
	}
}

void APlayerCharacter::MoveRight(float Scalar)
{
	if (Scalar != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Scalar);
	}
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	if (SpringArm)
	{
		FRotator CameraRelativeRot = SpringArm->RelativeRotation;

		const float CameraNewPitch = FMath::ClampAngle(CameraRelativeRot.Pitch + Rate * BaseLookUprate * GetWorld()->DeltaTimeSeconds, CameraPitchMin, CameraPitchMax);

		CameraRelativeRot.Pitch = CameraNewPitch;

		SpringArm->SetRelativeRotation(CameraRelativeRot);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
}

void APlayerCharacter::SpawnShootingParticles(FVector ParticleLocation)
{
	if (TrailEffect)
	{
		UParticleSystemComponent *SpawnedParticle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), TrailEffect, GunMesh->GetSocketLocation(FName("Muzzle")));
		SpawnedParticle->SetWorldScale3D(FVector(5.0f));
		SpawnedParticle->SetVectorParameter(FName("ShocKBeamEnd"), ParticleLocation);
	}

	if (HitEffect)
	{
		UParticleSystemComponent *SpawnedParticle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), HitEffect, ParticleLocation, FRotator::ZeroRotator, true);

		SpawnedParticle->SetWorldScale3D(FVector(0.25f));
	}

}


