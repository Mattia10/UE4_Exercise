// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Runtime/engine/Classes/Curves/CurveVector.h"
#include "SC_MoveByVector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PROJECT_API USC_MoveByVector : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USC_MoveByVector();
	UPROPERTY(editanywhere)
	UCurveVector *CurveVector;
	float ElapsedTime;
	float CurveMaxTime;
	float Speed;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
};
