// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UHUDWidget::UpdateCurrentAmmo(uint8 CurrentAmmo)
{
	AmmoText->SetText(FText::FromString(FString::FromInt(CurrentAmmo)));
}

void UHUDWidget::UpdateMaxAmmo(uint8 MaxAmmo)
{
	MaxAmmoText->SetText(FText::FromString(FString::FromInt(MaxAmmo)));
}

void UHUDWidget::UpdateCurrentClipAmmo(uint8 CurrentClipAmmo)
{
	ClipAmmoText->SetText(FText::FromString(FString::FromInt(CurrentClipAmmo)));
}

void UHUDWidget::UpdateMaxClipAmmo(uint8 MaxClipAmmo)
{
	MaxClipAmmoText->SetText(FText::FromString(FString::FromInt(MaxClipAmmo)));
}

void UHUDWidget::UpdateKillCount(uint8 killCount)
{
	KillCount->SetText(FText::FromString(FString::FromInt(killCount)));
}

void UHUDWidget::UpdateKillGoal(uint8 killGoal)
{
	KillGoal->SetText(FText::FromString(FString::FromInt(killGoal)));
}

void UHUDWidget::OutOfAmmo(bool PopUp)
{
	if(PopUp)
	{
		OutOfAmmoText->SetVisibility(ESlateVisibility::Visible);
		OutOfAmmoImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		OutOfAmmoText->SetVisibility(ESlateVisibility::Hidden);
		OutOfAmmoImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UHUDWidget::SwitchHudWidget(uint8 index)
{
	HUDSwitcher->SetActiveWidgetIndex(index);
}
