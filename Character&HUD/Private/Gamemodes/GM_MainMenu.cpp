// Fill out your copyright notice in the Description page of Project Settings.

#include "Gamemodes/GM_MainMenu.h"

void AGM_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		if (APlayerController *Pc = GetWorld()->GetFirstPlayerController())
		{
			FInputModeUIOnly InputMode;

			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			Pc->SetInputMode(InputMode);
			Pc->bShowMouseCursor = true;

			UUserWidget *CreatedWidget = CreateWidget<UUserWidget>(Pc, MainMenuClass);
			CreatedWidget->AddToPlayerScreen();
		}
	}
}


