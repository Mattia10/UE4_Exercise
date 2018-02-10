// Fill out your copyright notice in the Description page of Project Settings.

#include "SC_MoveByVector.h"


// Sets default values for this component's properties
USC_MoveByVector::USC_MoveByVector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USC_MoveByVector::BeginPlay()
{
	Super::BeginPlay();

	ElapsedTime = 0;
	float min;
	CurveVector->GetTimeRange(min, CurveMaxTime);
	
}


// Called every frame
void USC_MoveByVector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ElapsedTime += DeltaTime * Speed;
	if (ElapsedTime > CurveMaxTime)
	{
		ElapsedTime -= CurveMaxTime;
	}

	FVector Position = CurveVector->GetVectorValue(ElapsedTime);
	SetRelativeLocation(Position);
}

