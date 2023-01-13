// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameJam/GameJamCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class GAMEJAM_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	//Setting and Getting health variable
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE void SetHealth(const float Val) { Health = Val; }
	
	//	Function for implement damage
	void TakingDamage(float Damage);
	
	//	Boolean for take damage animation 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool bTakenDamage = false;

	//	Boolean for dying animation 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
	bool bDead = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HealthWidgetComp;

	// Variable for represent current health
	float Health;

	// Variable for represent maximum health
	float MaxHealth = 100;

private:

	UPROPERTY()
	AGameJamCharacter* Player;
};
