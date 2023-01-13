// Fill out your copyright notice in the Description page of Project Settings.


#include "GameJamGameInstance.h"

#include "PlayerSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UGameJamGameInstance::SaveGame()
{
	if(UGameplayStatics::DoesSaveGameExist("GameJam",0))
	{
		UPlayerSaveGame* SavedGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot("GameJam",0));
		SavedGame->SetCurrentLevel(CurrentLevel);
		SavedGame->SetScore(Score);
		SavedGame->SetAvaibleUpgrade(AvaibleUpgrade);
		SavedGame->SetAmmoUpgrade(AmmoUpgrade);
		SavedGame->SetClipUpgrade(ClipUpgrade);
		SavedGame->SetDamageUpgrade(DamageUpgrade);
		SavedGame->SetReloadUpgrade(ReloadUpgrade);
		SavedGame->SetSpeedUpgrade(SpeedUpgrade);
		SavedGame->SetTotalUpgrade(TotalUpgrade);
		SavedGame->SetCurrentAmmo(CurrentAmmo);
		SavedGame->SetCurrentClipAmmo(CurrentClipAmmo);
		if(UGameplayStatics::SaveGameToSlot(SavedGame, "GameJam", 0))
		{
			UE_LOG(LogTemp,Warning,TEXT("Data Saved"))
		}
	}
	else
	{
		UPlayerSaveGame* SavedGame = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
		if(SavedGame)
		{
			SavedGame->SetCurrentLevel(CurrentLevel);
			SavedGame->SetScore(Score);
			SavedGame->SetAvaibleUpgrade(AvaibleUpgrade);
			SavedGame->SetAmmoUpgrade(AmmoUpgrade);
			SavedGame->SetClipUpgrade(ClipUpgrade);
			SavedGame->SetDamageUpgrade(DamageUpgrade);
			SavedGame->SetReloadUpgrade(ReloadUpgrade);
			SavedGame->SetSpeedUpgrade(SpeedUpgrade);
			SavedGame->SetTotalUpgrade(TotalUpgrade);
			SavedGame->SetCurrentAmmo(CurrentAmmo);
			SavedGame->SetCurrentClipAmmo(CurrentClipAmmo);
			if(UGameplayStatics::SaveGameToSlot(SavedGame, "GameJam", 0))
			{
				UE_LOG(LogTemp,Warning,TEXT("Data Saved"))
			}
		}
	}
}

void UGameJamGameInstance::LoadGame()
{
	UPlayerSaveGame* LoadGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot("GameJam",0));
	if(LoadGame)
	{
		CurrentLevel = LoadGame->GetCurrentLevel();
		Score = LoadGame->GetScore();
		AvaibleUpgrade= LoadGame->GetAvaibleUpgrade();
		AmmoUpgrade= LoadGame->GetAmmoUpgrade();
		ClipUpgrade= LoadGame->GetClipUpgrade();
		DamageUpgrade=LoadGame->GetDamageUpgrade();
		ReloadUpgrade=LoadGame->GetReloadUpgrade();
		SpeedUpgrade=LoadGame->GetSpeedUpgrade();
		TotalUpgrade=LoadGame->GetTotalUpgrade();
		CurrentAmmo=LoadGame->GetCurrentAmmo();
		CurrentClipAmmo=LoadGame->GetCurrentClipAmmo();
	}
}

void UGameJamGameInstance::NewGame()
{
	CurrentLevel=1;
	AvaibleUpgrade = 0;
	AmmoUpgrade = 0;
	SpeedUpgrade = 0;
	TotalUpgrade = 0;
	ClipUpgrade = 0;
	ReloadUpgrade = 0;
	DamageUpgrade = 0;
	CurrentClipAmmo=15;
}
