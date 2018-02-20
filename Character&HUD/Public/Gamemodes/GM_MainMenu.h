// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GM_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class EXAMPLEPROJECT2_API AGM_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

protected:
		virtual void BeginPlay() override;
		
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Main Menu")
			class TSubclassOf<UUserWidget> MainMenuClass;
	
	
};
