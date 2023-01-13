// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthBar.h"
#include <Components/ProgressBar.h>

void UEnemyHealthBar::UpdateHealth(float Health)
{
	HealthBar->SetPercent(Health / 100);
}
