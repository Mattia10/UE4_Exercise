// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayElements/PickUp_Actor.h"


// Sets default values
APickUp_Actor::APickUp_Actor()
{
	RootComponent = CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));

	if (CollectionSphere)
	{
		//ignore every other channel
		CollectionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
		//only register pawns that overlap this actor
		CollectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		//bind the OnComponentBeginOverlap delegate to our function
		CollectionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUp_Actor::OnSphereOverlap);
	}
}

void APickUp_Actor::OnCollection_Implementation(APlayerCharacter * Collector)
{
	Destroy();
}

void APickUp_Actor::OnSphereOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		OnCollection(Player);
	}
}



