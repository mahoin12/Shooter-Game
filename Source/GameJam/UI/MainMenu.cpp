// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "GameJam/GameJamGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);
	StartButton->OnClicked.AddDynamic(this, &UMainMenu::Start);
	NewGameButton->OnClicked.AddDynamic(this, &UMainMenu::NewGame);
	ContinueButton->OnClicked.AddDynamic(this, &UMainMenu::Continue);
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::Back);
	ClipLeft->OnClicked.AddDynamic(this, &UMainMenu::ClipLeftP);
	ClipRight->OnClicked.AddDynamic(this, &UMainMenu::ClipRightP);
	SpeedLeft->OnClicked.AddDynamic(this, &UMainMenu::SpeedLeftP);
	SpeedRight->OnClicked.AddDynamic(this, &UMainMenu::SpeedRightP);
	DamageLeft->OnClicked.AddDynamic(this, &UMainMenu::DamageLeftP);
	DamageRight->OnClicked.AddDynamic(this, &UMainMenu::DamageRightP);
	TotalLeft->OnClicked.AddDynamic(this, &UMainMenu::TotalLeftP);
	TotalRight->OnClicked.AddDynamic(this, &UMainMenu::TotalRightP);
	AmmoLeft->OnClicked.AddDynamic(this, &UMainMenu::AmmoLeftP);
	AmmoRight->OnClicked.AddDynamic(this, &UMainMenu::AmmoRightP);
	ReloadLeft->OnClicked.AddDynamic(this, &UMainMenu::ReloadLeftP);
	ReloadRight->OnClicked.AddDynamic(this, &UMainMenu::ReloadRightP);

	GameInstance = Cast<UGameJamGameInstance>(GetGameInstance());
	GameInstance->LoadGame();

	ScoreText->SetText(FText::FromString(FString::FromInt(GameInstance->GetScore())));
	CurrentLevelText->SetText(FText::FromString(FString::FromInt(GameInstance->GetCurrentLevel())));
}

void UMainMenu::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),0,EQuitPreference::Quit,false);
}

void UMainMenu::Start()
{
	GameInstance->SetAvaibleUpgrade(AvaibleUpgrade);
	GameInstance->SetAmmoUpgrade(AmmoUpgrade);
	GameInstance->SetClipUpgrade(ClipUpgrade);
	GameInstance->SetDamageUpgrade(DamageUpgrade);
	GameInstance->SetReloadUpgrade(ReloadUpgrade);
	GameInstance->SetSpeedUpgrade(SpeedUpgrade);
	GameInstance->SetTotalUpgrade(TotalUpgrade);
	UGameplayStatics::OpenLevel(GetWorld(),"TopDownMap",true);
}

void UMainMenu::NewGame()
{
	GameInstance->NewGame();
	UGameplayStatics::OpenLevel(GetWorld(),"TopDownMap",true);
}

void UMainMenu::Continue()
{
	GameInstance->LoadGame();
	
	MainMenuSwicther->SetActiveWidgetIndex(1);
	
	AvaibleUpgrade= GameInstance->GetAvaibleUpgrade();
	AmmoUpgrade= GameInstance->GetAmmoUpgrade();
	ClipUpgrade= GameInstance->GetClipUpgrade();
	DamageUpgrade=GameInstance->GetDamageUpgrade();
	ReloadUpgrade=GameInstance->GetReloadUpgrade();
	SpeedUpgrade=GameInstance->GetSpeedUpgrade();
	TotalUpgrade=GameInstance->GetTotalUpgrade();

	AmmoPip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("DefaultOption"),AmmoUpgrade);
	ClipPip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("DefaultOption"),ClipUpgrade);
	DamagePip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("DefaultOption"),DamageUpgrade);
	ReloadPip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("DefaultOption"),ReloadUpgrade);
	SpeedPip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("DefaultOption"),SpeedUpgrade);
	TotalPip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("DefaultOption"),TotalUpgrade);
	
	UpdateClip();
	UpdateSpeed();
	UpdateTotal();
	UpdateAvaible();
	UpdateDamage();
	UpdateAmmo();
	UpdateReload();
	
}

void UMainMenu::Back()
{
	MainMenuSwicther->SetActiveWidgetIndex(0);
}

void UMainMenu::ClipLeftP()
{
	if(ClipUpgrade>GameInstance->GetClipUpgrade())
	{
		ClipUpgrade--;
		AvaibleUpgrade++;
		UpdateClip();
		UpdateAvaible();
	}
}

void UMainMenu::ClipRightP()
{
	if(AvaibleUpgrade>0)
	{
		AvaibleUpgrade--;
		ClipUpgrade++;
		UpdateClip();
		UpdateAvaible();
	}
}

void UMainMenu::SpeedLeftP()
{
	if(SpeedUpgrade>GameInstance->GetSpeedUpgrade())
	{
		SpeedUpgrade--;
		AvaibleUpgrade++;
		UpdateSpeed();
		UpdateAvaible();
	}
}

void UMainMenu::SpeedRightP()
{
	if(AvaibleUpgrade>0)
	{
		AvaibleUpgrade--;
		SpeedUpgrade++;
		UpdateSpeed();
		UpdateAvaible();
	}
}

void UMainMenu::DamageLeftP()
{
	if(DamageUpgrade>GameInstance->GetDamageUpgrade())
	{
		DamageUpgrade--;
		AvaibleUpgrade++;
		UpdateDamage();
		UpdateAvaible();
	}
}

void UMainMenu::DamageRightP()
{
	if(AvaibleUpgrade>0)
	{
		AvaibleUpgrade--;
		DamageUpgrade++;
		UpdateDamage();
		UpdateAvaible();
	}
}

void UMainMenu::TotalLeftP()
{
	if(TotalUpgrade>GameInstance->GetTotalUpgrade())
	{
		TotalUpgrade--;
		AvaibleUpgrade++;
		UpdateTotal();
		UpdateAvaible();
	}
}

void UMainMenu::TotalRightP()
{
	if(AvaibleUpgrade>0)
	{
		AvaibleUpgrade--;
		TotalUpgrade++;
		UpdateTotal();
		UpdateAvaible();
	}
}

void UMainMenu::AmmoLeftP()
{
	if(AmmoUpgrade>GameInstance->GetAmmoUpgrade())
	{
		AmmoUpgrade--;
		AvaibleUpgrade++;
		UpdateAmmo();
		UpdateAvaible();
	}
}

void UMainMenu::AmmoRightP()
{
	if(AvaibleUpgrade>0)
	{
		AvaibleUpgrade--;
		AmmoUpgrade++;
		UpdateAmmo();
		UpdateAvaible();
	}
}

void UMainMenu::ReloadLeftP()
{
	if(ReloadUpgrade>GameInstance->GetReloadUpgrade())
	{
		ReloadUpgrade--;
		AvaibleUpgrade++;
		UpdateReload();
		UpdateAvaible();
	}
}

void UMainMenu::ReloadRightP()
{
	if(AvaibleUpgrade>0)
	{
		AvaibleUpgrade--;
		ReloadUpgrade++;
		UpdateReload();
		UpdateAvaible();
	}
}

void UMainMenu::UpdateClip()
{
	ClipText->SetText(FText::FromString("Max Clip Amount: +"+FString::FromInt(2*ClipUpgrade)));
	ClipPip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("SelectedOption"),ClipUpgrade);
}

void UMainMenu::UpdateSpeed()
{
	SpeedText->SetText(FText::FromString("Max Speed: +"+FString::FromInt(SpeedUpgrade*10)));
	SpeedPip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("SelectedOption"),SpeedUpgrade);
}

void UMainMenu::UpdateTotal()
{
	TotalText->SetText(FText::FromString("Max Total Ammo: +"+FString::FromInt(TotalUpgrade*10)));
	TotalPip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("SelectedOption"),TotalUpgrade);
}

void UMainMenu::UpdateAvaible()
{
	AvaibleUpgradeText->SetText(FText::FromString(FString::FromInt(AvaibleUpgrade)));
}

void UMainMenu::UpdateDamage()
{
	DamageText->SetText(FText::FromString("Increased Damage: +"+FString::FromInt(DamageUpgrade)));
	DamagePip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("SelectedOption"),DamageUpgrade);
}

void UMainMenu::UpdateAmmo()
{
	AmmoText->SetText(FText::FromString("Gainable Ammo: +"+FString::FromInt(AmmoUpgrade)));
	AmmoPip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("SelectedOption"),AmmoUpgrade);
}

void UMainMenu::UpdateReload()
{
	ReloadText->SetText(FText::FromString("Reload Time: -"+FString::SanitizeFloat((float)ReloadUpgrade/10)+"sn"));
	ReloadPip->GetDynamicMaterial()->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("SelectedOption"),ReloadUpgrade);
}
