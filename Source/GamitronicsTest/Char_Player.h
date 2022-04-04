// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Char_Player.generated.h"

UCLASS()
class GAMITRONICSTEST_API AChar_Player : public ACharacter
{
	GENERATED_BODY()

	//Variable set to true if player is dead
	bool bIsDead;

protected:
	//Health of Player/AI
	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo", meta = (ClampMin = "0.0", UIMin = "0.0"))
	int Ammo;

	UPROPERTY(EditDefaultsOnly, Category = "Rage", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Rage;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Component that holds the camera
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	//Component to hold the player camera
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleDefaultsOnly, Category = "Gun")
	class AGun* SpawnedGun;

public:	
	// Sets default values for this character's properties
	AChar_Player();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Functions to handle movement of player
	UFUNCTION()
	virtual void MoveForward(float AxisValue);

	UFUNCTION()
	virtual void MoveRight(float AxisValue);

	UPROPERTY(EditDefaultsOnly, Category = "Gun")
	TSubclassOf<class AGun> GunToSpawn;

	UFUNCTION()
	void FireGun();

	UFUNCTION(BlueprintPure)
	float ReturnHealth();

	UFUNCTION(BlueprintPure)
	int ReturnAmmo();

	UFUNCTION(BlueprintPure)
	float ReturnRage();

	UFUNCTION(BlueprintPure)
	bool ReturnIsDead();

	UFUNCTION()
	void ApplyHealthDamage(int DamageAmount);
};
