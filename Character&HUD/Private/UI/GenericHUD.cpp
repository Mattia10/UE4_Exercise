// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GenericHUD.h"
class UUserWidget;

AGenericHUD::AGenericHUD()
{
	GameplayHUDClass = NULL;

	DeadMenuClass = NULL;

	PauseMenuClass = NULL;
}

bool AGenericHUD::ShowSpecificMenu(TSubclassOf<UUserWidget> ClassToShow, bool GameOnly, bool ShowMouse)
{
	HideAllMenus();

	if (ClassToShow)
	{
		//create widget then add to screen
		UUserWidget *CreatedWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), ClassToShow);
		CreatedWidget->AddToPlayerScreen();

		if (GameOnly)
		{
			//set our input mode to game only-> full control of the player
			GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
		}
		else
		{
			FInputModeUIOnly InputMode;

			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			GetOwningPlayerController()->SetInputMode(InputMode);
		}

		GetOwningPlayerController()->bShowMouseCursor = ShowMouse;

		return true;
	}
	return false;
}

void AGenericHUD::HideAllMenus()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

