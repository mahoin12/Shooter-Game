// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class GAMEJAM_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateCurrentAmmo(uint8 CurrentAmmo);
	
	void UpdateMaxAmmo(uint8 MaxAmmo);

	void UpdateCurrentClipAmmo(uint8 CurrentClipAmmo);
	
	void UpdateMaxClipAmmo(uint8 MaxClipAmmo);

	void UpdateKillCount(uint8 killCount);
	
	void UpdateKillGoal(uint8 killGoal);

	void OutOfAmmo(bool PopUp);

	void SwitchHudWidget(uint8 index);

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AmmoText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxAmmoText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClipAmmoText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxClipAmmoText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OutOfAmmoText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillGoal;

	UPROPERTY(meta = (BindWidget))
	UImage* OutOfAmmoImage;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* HUDSwitcher;
};
