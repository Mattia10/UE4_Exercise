// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/GM_Gameplay.h"

void AGM_Gameplay::RespawnPlayer(AController *NewPlayer)
{
	if (NewPlayer)
	{
		NewPlayer->GetPawn()->Destroy();
		RestartPlayer(NewPlayer);
	}
}


