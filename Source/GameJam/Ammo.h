// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo.generated.h"

class UStaticMeshComponent;
UCLASS()
class GAMEJAM_API AAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmo();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance")
	class UInstancedStaticMeshComponent* AmmoInstance;
	
protected:

	virtual void BeginPlay() override;
};
