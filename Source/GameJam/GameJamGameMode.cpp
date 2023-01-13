// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameJamGameMode.h"
#include "GameJamPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/CharacterHUD.h"
#include "UI/MainMenu.h"
#include "UObject/ConstructorHelpers.h"

AGameJamGameMode::AGameJamGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGameJamPlayerController::StaticClass();
	
	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	
	if(UGameplayStatics::GetCurrentLevelName(GetWorld(),true)!="MainMenu")
	{
		// set default pawn class to our Blueprinted character
		static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
		if (PlayerPawnBPClass.Class != nullptr)
		{
			DefaultPawnClass = PlayerPawnBPClass.Class;
		}

		HUDClass = ACharacterHUD::StaticClass();
	}
	else
	{
		static ConstructorHelpers::FClassFinder<UMainMenu> BP_HUDWidget(TEXT("/Game/UI/BP_MainMenu"));
		if (!ensure(BP_HUDWidget.Class != nullptr)) return;

		MainMenu = CreateWidget<UMainMenu>(GetWorld(),BP_HUDWidget.Class);

		if(MainMenu)
			MainMenu->AddToViewport(0);
	}
}