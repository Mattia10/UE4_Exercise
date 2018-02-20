// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayElements/Destructible_Actor.h"

// Sets default values
ADestructible_Actor::ADestructible_Actor()
{
	RootComponent = Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (Mesh)
	{
		Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	}

	MaxHealth = 25.0f;
	CurrentHealth = MaxHealth;

	DestructionRadius = 400.0f;
	DestructionDamage = 25.0f;
}

// Called when the game starts or when spawned
void ADestructible_Actor::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentHealth != MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
	
}

void ADestructible_Actor::OnDeath_Implementation()
{
	{
		TArray<FOverlapResult> Overlaps;

		const FVector StartPos = Mesh->GetComponentLocation();

		FCollisionShape Sphere = FCollisionShape::MakeSphere(DestructionRadius);

		if (GetWorld()->OverlapMultiByChannel(Overlaps, StartPos, FQuat::Identity, ECC_WorldDynamic, Sphere))
		{
			for (int index = 0; index < Overlaps.Num(); index++)
			{
				TSubclassOf<UDamageType> const ValideDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());

				FDamageEvent DamageEvent(ValideDamageTypeClass);

				Overlaps[index].GetActor()->TakeDamage(DestructionDamage, DamageEvent, nullptr, this);
			}
		}
	}
	Destroy();
}

float ADestructible_Actor::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentHealth <= 0.0f)
	{
		return 0.0f;
	}

	const float SubtractedHealth = CurrentHealth - DamageAmount;
	//check if the subtracted health is equal or lower 0
	if (FMath::IsNearlyZero(SubtractedHealth) || SubtractedHealth < 0.0f)
	{
		//if is 0, call Death function
		CurrentHealth = 0.0f;
		OnDeath();
	}
	else
	{
		//set the Health
		CurrentHealth = SubtractedHealth;
	}

	return CurrentHealth;
}


