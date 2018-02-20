// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "PickUp_Actor.generated.h"

UCLASS()
class EXAMPLEPROJECT2_API APickUp_Actor : public AActor
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
			class USphereComponent *CollectionSphere;

public:	
	// Sets default values for this actor's properties
	APickUp_Actor();

protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup_Actor")
		void OnCollection(class APlayerCharacter *Collector);
	void OnCollection_Implementation(class APlayerCharacter *Collector);

private:

	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

};
