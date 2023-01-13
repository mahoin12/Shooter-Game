// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameJamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API UGameJamGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	void SaveGame();
	
	void LoadGame();

	void NewGame();

	FORCEINLINE uint8 GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE void SetCurrentLevel(const uint8 Val) { CurrentLevel = Val; }
	FORCEINLINE uint64 GetScore() const { return Score; }
	FORCEINLINE void SetScore(const uint64 Val) { Score += Val; }
	FORCEINLINE uint8 GetAvaibleUpgrade() const { return AvaibleUpgrade; }
	FORCEINLINE void SetAvaibleUpgrade(const uint8 Val) { AvaibleUpgrade = Val; }
	FORCEINLINE uint8 GetAmmoUpgrade() const { return AmmoUpgrade; }
	FORCEINLINE void SetAmmoUpgrade(const uint8 Val) { AmmoUpgrade = Val; }
	FORCEINLINE uint8 GetSpeedUpgrade() const { return SpeedUpgrade; }
	FORCEINLINE void SetSpeedUpgrade(const uint8 Val) { SpeedUpgrade = Val; }
	FORCEINLINE uint8 GetTotalUpgrade() const { return TotalUpgrade; }
	FORCEINLINE void SetTotalUpgrade(const uint8 Val) { TotalUpgrade = Val; }
	FORCEINLINE uint8 GetClipUpgrade() const { return ClipUpgrade; }
	FORCEINLINE void SetClipUpgrade(const uint8 Val) { ClipUpgrade = Val; }
	FORCEINLINE uint8 GetReloadUpgrade() const { return ReloadUpgrade; }
	FORCEINLINE void SetReloadUpgrade(const uint8 Val) { ReloadUpgrade = Val; }
	FORCEINLINE uint8 GetDamageUpgrade() const { return DamageUpgrade; }
	FORCEINLINE void SetDamageUpgrade(const uint8 Val) { DamageUpgrade = Val; }
	FORCEINLINE uint8 GetCurrentAmmo() const { return CurrentAmmo; }
	FORCEINLINE void SetCurrentAmmo(const uint8 Val) { CurrentAmmo = Val; }
	FORCEINLINE uint8 GetCurrentClipAmmo() const { return CurrentClipAmmo; }
	FORCEINLINE void SetCurrentClipAmmo(const uint8 Val) { CurrentClipAmmo = Val; }

protected:

private:

	uint8 CurrentLevel=1;

	uint64 Score = 0;

	uint8 AvaibleUpgrade = 0;

	uint8 AmmoUpgrade = 0;
	uint8 SpeedUpgrade = 0;
	uint8 TotalUpgrade = 0;
	uint8 ClipUpgrade = 0;
	uint8 ReloadUpgrade = 0;
	uint8 DamageUpgrade = 0;
	uint8 CurrentAmmo = 50;
	uint8 CurrentClipAmmo = 15;
};
