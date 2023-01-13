// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterHUD.h"
#include "HUDWidget.h"

ACharacterHUD::ACharacterHUD()
{
	static ConstructorHelpers::FClassFinder<UHUDWidget> BP_HUDWidget(TEXT("/Game/UI/BP_HUDWidget"));
	if (!ensure(BP_HUDWidget.Class != nullptr)) return;

	HUDWidget = CreateWidget<UHUDWidget>(GetWorld(),BP_HUDWidget.Class);

	if(HUDWidget)
		HUDWidget->AddToViewport(0);
}
