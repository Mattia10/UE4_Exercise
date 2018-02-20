// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widget_Gameplay.h"
#include "Runtime/Core/Public/Internationalization//Text.h"
#include "PlayerCharacter.h"

float UWidget_Gameplay::GetCurrentHealth()
{
	if (APlayerCharacter *Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		return (FMath::Clamp<float>(Player->GetCurrentHealth() / Player->GetMaxHealth(), 0.0f, 1.0f));
	}
	return 0.5f;
}

FText UWidget_Gameplay::GetCurrentAmmo()
{
	if (APlayerCharacter *Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		return FText::AsNumber(Player->GetCurrentAmmo());
	}
	return FText::AsNumber(999);
}
