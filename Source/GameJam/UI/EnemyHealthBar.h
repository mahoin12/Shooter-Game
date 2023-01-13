// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API UEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateHealth(float Health);
	
protected:

	//Binding progress bar as HealthBar
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
};
