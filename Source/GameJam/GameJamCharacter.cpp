// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameJamCharacter.h"
#include "Ammo.h"
#include "GameJamGameInstance.h"
#include "GameJamPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Enemy/Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/CharacterHUD.h"
#include "UI/HUDWidget.h"

AGameJamCharacter::AGameJamCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	/*Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);
	Weapon->SetRelativeRotation(FRotator(0,0,-90));*/
	
	/*Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), UKismetStringLibrary::Conv_StringToName("ik_hand_gun"));
	Weapon->SetRelativeRotation(FRotator(0,0,-90));

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	NiagaraComponent->SetupAttachment(Weapon, UKismetStringLibrary::Conv_StringToName("Muzzle"));
	NiagaraComponent->SetupAttachment(GetMesh());*/
	/*static ConstructorHelpers::FClassFinder<AEnemy> Bp_UnsurKarakter(
		TEXT("/Game/Bp_Enemy"));
	EnemyBP = Bp_UnsurKarakter.Class;*/
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGameJamCharacter::OnOverlapBegin);
}

void AGameJamCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AGameJamCharacter::UpdateAmmo(uint8 AmmoChange)
{
	TotalAmmo+=AmmoChange;
	if(TotalAmmo>MaxTotalAmmo)
		TotalAmmo=MaxTotalAmmo;
	CharacterHUDWidget->UpdateCurrentAmmo(TotalAmmo);
}

void AGameJamCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		// For get and set ammo quantity after that destroy actor
		if (class AAmmo* Ammo = Cast<AAmmo>(OtherActor))
		{
			Ammo->AmmoInstance->RemoveInstance(OtherBodyIndex);
			UpdateAmmo(1+UKismetMathLibrary::RandomInteger(9)+GameInstance->GetAmmoUpgrade());
		}
		else if (OtherActor->GetClass()==AEnemy::StaticClass())
		{
			CharacterHUDWidget->SwitchHudWidget(1);
			FTimerHandle Handle1;
			GetWorld()->GetTimerManager().SetTimer(Handle1,this,&AGameJamCharacter::MainMenu, 5,false, 5);
		}
	}
}

void AGameJamCharacter::IncreaseKillCount()
{
	KillCount++;
	CharacterHUDWidget->UpdateKillCount(KillCount);
	if(KillCount>=(GameInstance->GetCurrentLevel()+19))
	{
		GameInstance->SetAvaibleUpgrade(GameInstance->GetAvaibleUpgrade()+1);
		GameInstance->SetCurrentLevel(GameInstance->GetCurrentLevel()+1);
		GameInstance->SetScore(KillCount);
		GameInstance->SaveGame();
		UGameplayStatics::OpenLevel(GetWorld(),"MainMenu",true);
	}
}

void AGameJamCharacter::Fire()
{
	if(ClipAmmo>0)
	{
		ClipAmmo--;
		FHitResult Hit;
		FVector Start = GetActorLocation();
		uint32 LineWidth = 4000;
		FVector End = -GetCapsuleComponent()->GetForwardVector()*(LineWidth)+Start;
		FCollisionQueryParams HatParameterleri;
		TArray<AActor*> ignore;
		ignore.Add(this);
		if(UKismetSystemLibrary::LineTraceSingle(GetWorld(),Start,End,UEngineTypes::ConvertToTraceType(ECC_WorldStatic),false,ignore,EDrawDebugTrace::None,Hit,true))
		{
			if(Hit.GetActor()->GetClass()==AEnemy::StaticClass())
			{
				AEnemy* Enemy = Cast<AEnemy>(Hit.GetActor());
				if(Enemy)
				{
					uint8 Damage = 5+UKismetMathLibrary::RandomInteger(20)+GameInstance->GetDamageUpgrade();
					Enemy->TakingDamage(Damage);
				}
			}
		}
		bFire=true;
		PlayAnimMontage(FireMontage);
	}
	else
	{
		Reload();
	}
	CharacterHUDWidget->UpdateCurrentAmmo(TotalAmmo);
	CharacterHUDWidget->UpdateCurrentClipAmmo(ClipAmmo);
}

void AGameJamCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterController = Cast<AGameJamPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));

	CharacterHUDWidget = Cast<ACharacterHUD>(CharacterController->GetHUD())->GetHUDWidget();

	GameInstance = Cast<UGameJamGameInstance>(GetGameInstance());

	GetCharacterMovement()->MaxWalkSpeed+=GameInstance->GetSpeedUpgrade()*10;
	MaxTotalAmmo=100+GameInstance->GetTotalUpgrade()*10;
	MaxClipAmmo=15+GameInstance->GetClipUpgrade()*2;
	TotalAmmo=GameInstance->GetCurrentAmmo();
	ReloadTime=2-GameInstance->GetReloadUpgrade()*0.1;
	ClipAmmo=GameInstance->GetCurrentClipAmmo();
	CurrentLevel=GameInstance->GetCurrentLevel();
	
	CharacterHUDWidget->UpdateCurrentAmmo(TotalAmmo);
	CharacterHUDWidget->UpdateMaxAmmo(MaxTotalAmmo);
	CharacterHUDWidget->UpdateCurrentClipAmmo(ClipAmmo);
	CharacterHUDWidget->UpdateMaxClipAmmo(MaxClipAmmo);
	CharacterHUDWidget->UpdateKillCount(KillCount);
	CharacterHUDWidget->UpdateKillGoal(GameInstance->GetCurrentLevel()+19);

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle,this,&AGameJamCharacter::SpawnEnemy, 3,true, 3);
}

void AGameJamCharacter::SpawnEnemy()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for(uint8 i=0;i<(CurrentLevel);i++)
	{
		FVector RandomRelativeKonum = (UKismetMathLibrary::RandomUnitVector())*9900;
		RandomRelativeKonum.Z=0;
		GetWorld()->SpawnActor<AEnemy>(AEnemy::StaticClass(), RandomRelativeKonum,
						FRotator::ZeroRotator, SpawnParameters);
	}
}

void AGameJamCharacter::Reload()
{
	if(!bReloading && TotalAmmo>0)
	{
		bReloading=true;
		PlayAnimMontage(ReloadMontage);
		float Reload = GameInstance->GetReloadUpgrade();
		FTimerHandle Handle2;
		GetWorld()->GetTimerManager().SetTimer(Handle2,this,&AGameJamCharacter::ReloadCalc, ReloadTime,false, ReloadTime);
	}
}

void AGameJamCharacter::MainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(),"MainMenu",true);
}

void AGameJamCharacter::ReloadCalc()
{
	int temp = TotalAmmo;
	temp-=(MaxClipAmmo-ClipAmmo);
	if(temp<0)
	{
		ClipAmmo+=TotalAmmo;
		TotalAmmo=0;
	}
	else
	{
		TotalAmmo-=(MaxClipAmmo-ClipAmmo);
		ClipAmmo=MaxClipAmmo;
	}
	bReloading=false;
	CharacterHUDWidget->UpdateCurrentAmmo(TotalAmmo);
	CharacterHUDWidget->UpdateCurrentClipAmmo(ClipAmmo);
}

