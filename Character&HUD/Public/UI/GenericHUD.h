// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/public/Blueprint/WidgetLayoutLibrary.h"
#include "GenericHUD.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class EXAMPLEPROJECT2_API AGenericHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AGenericHUD();

	class TSubclassOf<UUserWidget> GetGameplayHUDClass() const { return GameplayHUDClass; }
	class TSubclassOf<UUserWidget> GetDeadMenuClass() const { return DeadMenuClass; }
	class TSubclassOf<UUserWidget> GetPauseMenuClass() const { return PauseMenuClass; }

	bool ShowSpecificMenu(class TSubclassOf<UUserWidget> ClassToShow, bool GameOnly, bool ShowMouse);

	//Hide other menù
	UFUNCTION(BlueprintCallable, Category = "GenericHUD")
		void HideAllMenus();

protected:
	//HUD for the player
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GenericHUD")
		class TSubclassOf<UUserWidget> GameplayHUDClass;
	//HUD when player dead
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GenericHUD")
		class TSubclassOf<UUserWidget> DeadMenuClass;
	//HUD for the pause menù
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GenericHUD")
		class TSubclassOf<UUserWidget> PauseMenuClass;



	
	
	
};
