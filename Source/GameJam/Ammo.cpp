// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"

#include "GameJamGameInstance.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAmmo::AAmmo()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AlternateMeshAsset(TEXT("/Game/MS_MilitaryEquipment/3D_Assets/Military_Wooden_Box_00/ucooedgfa_LOD0"));
	// Create the Root Component
	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	}
	AmmoInstance = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMesh"));
	AmmoInstance->SetupAttachment(GetRootComponent());
	AmmoInstance->SetStaticMesh(AlternateMeshAsset.Object);
	AmmoInstance->SetCollisionProfileName("OverlapOnlyPawn");
	AmmoInstance->bMultiBodyOverlap=true;
}

void AAmmo::BeginPlay()
{
	Super::BeginPlay();

	UGameJamGameInstance* GameInstance = Cast<UGameJamGameInstance>(GetGameInstance());
	uint16 AmmoAmount = 400-GameInstance->GetCurrentLevel()*2;
	for(uint16 i=0; i<AmmoAmount;i++)
	{
		FVector RandomRelativeKonum = UKismetMathLibrary::RandomUnitVector()*9900;
		RandomRelativeKonum.Z=0;
		AmmoInstance->AddInstance(FTransform(FRotator(0,UKismetMathLibrary::RandomFloat(),0),RandomRelativeKonum, FVector::One()),false);
	}
}

