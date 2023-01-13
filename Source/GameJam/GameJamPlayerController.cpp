// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameJamPlayerController.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "GameJamCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

AGameJamPlayerController::AGameJamPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AGameJamPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	GameJamCharacter = Cast<AGameJamCharacter>(GetPawn());

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AGameJamPlayerController::Foward(const FInputActionValue& X)
{
	if(GameJamCharacter)
		GameJamCharacter->AddMovementInput(FVector(X.GetMagnitude(),0,0),1);
}

void AGameJamPlayerController::Back(const FInputActionValue& X)
{
	if(GameJamCharacter)
		GameJamCharacter->AddMovementInput(FVector(-X.GetMagnitude(),0,0),1);
}

void AGameJamPlayerController::Right(const FInputActionValue& X)
{
	if(GameJamCharacter)
		GameJamCharacter->AddMovementInput(FVector(0,X.GetMagnitude(),0),1);
}

void AGameJamPlayerController::Left(const FInputActionValue& X)
{
	if(GameJamCharacter)
		GameJamCharacter->AddMovementInput(FVector(0,-X.GetMagnitude(),0),1);
}

void AGameJamPlayerController::ZoomInFunc(const FInputActionValue& X)
{
	if(GameJamCharacter)
	{
		GameJamCharacter->GetCameraBoom()->TargetArmLength-=(100*X.GetMagnitude());
		if(GameJamCharacter->GetCameraBoom()->TargetArmLength < 1500)
			GameJamCharacter->GetCameraBoom()->TargetArmLength=1500;
	}
}

void AGameJamPlayerController::ZoomOutFunc(const FInputActionValue& X)
{
	if(GameJamCharacter)
	{
		GameJamCharacter->GetCameraBoom()->TargetArmLength+=(100*X.GetMagnitude());
		if(GameJamCharacter->GetCameraBoom()->TargetArmLength > 5000)
			GameJamCharacter->GetCameraBoom()->TargetArmLength=5000;
	}
}

void AGameJamPlayerController::Fire()
{
	if(GameJamCharacter)
		GameJamCharacter->Fire();
}

void AGameJamPlayerController::Reload()
{
	if(GameJamCharacter)
		GameJamCharacter->Reload();
}

void AGameJamPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(WPress,ETriggerEvent::Triggered,this,&AGameJamPlayerController::Foward);
		EnhancedInputComponent->BindAction(SPress,ETriggerEvent::Triggered,this,&AGameJamPlayerController::Back);
		EnhancedInputComponent->BindAction(DPress,ETriggerEvent::Triggered,this,&AGameJamPlayerController::Right);
		EnhancedInputComponent->BindAction(APress,ETriggerEvent::Triggered,this,&AGameJamPlayerController::Left);
		EnhancedInputComponent->BindAction(ZoomIn,ETriggerEvent::Triggered,this,&AGameJamPlayerController::ZoomInFunc);
		EnhancedInputComponent->BindAction(ZoomOut,ETriggerEvent::Triggered,this,&AGameJamPlayerController::ZoomOutFunc);
		EnhancedInputComponent->BindAction(FirePress,ETriggerEvent::Triggered,this,&AGameJamPlayerController::Fire);
		EnhancedInputComponent->BindAction(ReloadPress,ETriggerEvent::Triggered,this,&AGameJamPlayerController::Reload);
	}
}

