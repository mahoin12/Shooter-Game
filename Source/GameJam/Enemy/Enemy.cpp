// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EnemyAIController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameJam/UI/EnemyHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemy::AEnemy()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AlternateMeshAsset(TEXT("/Game/Anim/copzombie_l_actisdato"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimObj(TEXT("/Game/Anim/Animasyon"));
	static ConstructorHelpers::FClassFinder<UEnemyHealthBar> WidgetObj(TEXT("/Game/UI/BP_EnemyHealthBar"));
	// Setting root component
	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}
	// Setting mesh component
	if (AlternateMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(AlternateMeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->SetRelativeRotation(FRotator(FRotator(0.0f, -90.0f, 0.0f)));
		GetCapsuleComponent()->SetRelativeScale3D(FVector(1, 1, 1));
	}

	// Setting animation object
	if (AnimObj.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimObj.Class);
	}

	// Setting widgets for health bar
	if (WidgetObj.Succeeded()) 
	{
		HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
		HealthWidgetComp->SetupAttachment(RootComponent);
		HealthWidgetComp->SetRelativeLocation(FVector(0, 0, 120.f));
		HealthWidgetComp->SetWidgetClass(WidgetObj.Class);
		HealthWidgetComp->SetCollisionProfileName("NoCollision");
		HealthWidgetComp->SetDrawSize(FVector2D(300, 30));
		HealthWidgetComp->SetCastShadow(false);
	}

	// Initial health equal to maxhealth
	Health = MaxHealth;

	// Settings for smooth chase player
	bUseControllerRotationYaw = false;
	// Second line is more effective
	// GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass=AEnemyAIController::StaticClass();

	GetCapsuleComponent()->SetCollisionProfileName("OverlapOnlyPawn");
}

void AEnemy::TakingDamage(float Damage)
{
	Health -= Damage;
	if (Health < 1)
	{
		Health = 0;
		if(!bDead)
		{
			Player->IncreaseKillCount();
			bDead = true;
		}
	}
	else
	{
		bTakenDamage = true;
	}
	Cast<UEnemyHealthBar>(HealthWidgetComp->GetWidget())->UpdateHealth(Health);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AGameJamCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
	Cast<UEnemyHealthBar>(HealthWidgetComp->GetWidget())->UpdateHealth(Health);
}


void AEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(!bDead)
	{
		FRotator BakisYonu = UKismetMathLibrary::FindLookAtRotation(HealthWidgetComp->GetComponentLocation(),Player->GetTopDownCameraComponent()->GetComponentLocation());
		HealthWidgetComp->SetWorldRotation(BakisYonu);
	}
}

