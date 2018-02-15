// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 10.0f;
	CurrentHealth = MaxHealth;
	bIsSprinting = false;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//set MaxHealth
	if (CurrentHealth != MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}


