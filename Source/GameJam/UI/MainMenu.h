// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class GAMEJAM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	
protected:
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void Quit();
	UFUNCTION()
	void Start();
	UFUNCTION()
	void NewGame();
	UFUNCTION()
	void Continue();
	UFUNCTION()
	void Back();
	UFUNCTION()
	void ClipLeftP();
	UFUNCTION()
	void ClipRightP();
	UFUNCTION()
	void SpeedLeftP();
	UFUNCTION()
	void SpeedRightP();
	UFUNCTION()
	void DamageLeftP();
	UFUNCTION()
	void DamageRightP();
	UFUNCTION()
	void TotalLeftP();
	UFUNCTION()
	void TotalRightP();
	UFUNCTION()
	void AmmoLeftP();
	UFUNCTION()
	void AmmoRightP();
	UFUNCTION()
	void ReloadLeftP();
	UFUNCTION()
	void ReloadRightP();

	void UpdateClip();
	void UpdateSpeed();
	void UpdateTotal();
	void UpdateAvaible();
	void UpdateDamage();
	void UpdateAmmo();
	void UpdateReload();
	
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
	UPROPERTY(meta = (BindWidget))
	UButton* NewGameButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ContinueButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ClipLeft;
	UPROPERTY(meta = (BindWidget))
	UButton* ClipRight;
	UPROPERTY(meta = (BindWidget))
	UButton* SpeedLeft;
	UPROPERTY(meta = (BindWidget))
	UButton* SpeedRight;
	UPROPERTY(meta = (BindWidget))
	UButton* DamageLeft;
	UPROPERTY(meta = (BindWidget))
	UButton* DamageRight;
	UPROPERTY(meta = (BindWidget))
	UButton* TotalLeft;
	UPROPERTY(meta = (BindWidget))
	UButton* TotalRight;
	UPROPERTY(meta = (BindWidget))
	UButton* AmmoLeft;
	UPROPERTY(meta = (BindWidget))
	UButton* AmmoRight;
	UPROPERTY(meta = (BindWidget))
	UButton* ReloadLeft;
	UPROPERTY(meta = (BindWidget))
	UButton* ReloadRight;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentLevelText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClipText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpeedText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AmmoText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ReloadText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AvaibleUpgradeText;
	
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MainMenuSwicther;

	UPROPERTY(meta = (BindWidget))
	UImage* ClipPip;
	UPROPERTY(meta = (BindWidget))
	UImage* SpeedPip;
	UPROPERTY(meta = (BindWidget))
	UImage* DamagePip;
	UPROPERTY(meta = (BindWidget))
	UImage* TotalPip;
	UPROPERTY(meta = (BindWidget))
	UImage* AmmoPip;
	UPROPERTY(meta = (BindWidget))
	UImage* ReloadPip;

private:

	UPROPERTY()
	class UGameJamGameInstance* GameInstance;

	uint8 AvaibleUpgrade = 0;

	uint8 AmmoUpgrade = 0;
	uint8 SpeedUpgrade = 0;
	uint8 TotalUpgrade = 0;
	uint8 ClipUpgrade = 0;
	uint8 ReloadUpgrade = 0;
	uint8 DamageUpgrade = 0;
};
