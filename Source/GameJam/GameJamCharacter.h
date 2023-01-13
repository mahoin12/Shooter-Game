// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameJamCharacter.generated.h"

class AEnemy;

UCLASS(Blueprintable)
class AGameJamCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AGameJamCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE uint16 GetAmmo() const { return TotalAmmo;};
	FORCEINLINE uint16 GetMaxAmmo() const { return MaxTotalAmmo;};
	void UpdateAmmo(uint8 AmmoChange);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void IncreaseKillCount();
	
	void Fire();

	void Reload();

	UPROPERTY(BlueprintReadWrite)
	bool bFire;

protected:
	/*// BP_GenelAsker referansını tutar.
	UPROPERTY(EditAnywhere, Category= "Karakter")
	TSubclassOf<AEnemy> EnemyBP;*/
	
private:
	
	virtual void BeginPlay() override;

	void SpawnEnemy();

	void MainMenu();

	void ReloadCalc();
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* NiagaraMuzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* NiagaraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Weapon;*/

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Weapon;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* GunReloadMontage;
	
	uint8 MaxTotalAmmo=0;
	uint8 MaxClipAmmo=0;
	uint8 TotalAmmo=0;
	uint8 ClipAmmo=0;
	uint8 CurrentLevel=0;

	uint8 KillCount=0;

	float ReloadTime=0;

	bool bPopUp;

	bool bReloading=false;

	UPROPERTY()
	class AGameJamPlayerController* CharacterController;

	UPROPERTY()
	class UHUDWidget* CharacterHUDWidget;

	UPROPERTY()
	class UGameJamGameInstance* GameInstance;
	
};

