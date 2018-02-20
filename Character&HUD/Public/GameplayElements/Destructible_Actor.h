// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "EngineMinimal.h"
#include "Destructible_Actor.generated.h"

UCLASS()
class EXAMPLEPROJECT2_API ADestructible_Actor : public AActor
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent *Mesh;
public:	
	// Sets default values for this actor's properties
	ADestructible_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Destructible|Death")
		void OnDeath();
	void OnDeath_Implementation();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent,
		class AController* EventInstigator, AActor *DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destructible|Death")
		float DestructionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destructible|Death")
		float DestructionDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destructible|Health")
		float MaxHealth;

	float CurrentHealth;
};
