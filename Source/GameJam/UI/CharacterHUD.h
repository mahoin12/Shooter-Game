// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CharacterHUD.generated.h"

class UHUDWidget;

/**
 * 
 */
UCLASS()
class GAMEJAM_API ACharacterHUD : public AHUD
{
	GENERATED_BODY()

public:

	ACharacterHUD();

	FORCEINLINE class UHUDWidget* GetHUDWidget() const { return HUDWidget; }

protected:

	UPROPERTY()
	UHUDWidget* HUDWidget;
	
};
