// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Char_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMITRONICSTEST_API AChar_PlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	//Variables to hold the mouse position
	FVector MouseWorldLocation;
	FVector MouseWorldDirection;

	//Variable to hold the boneRotation
	FRotator BoneNewRot;

	//Enemy Kill Count
	int EnemyKills;

protected:
	//Variable to hold the pawn
	class AChar_Player* CharPlayer;

	//Widget To store the current PauseUI
	class UUserWidget* CurrentPauseWidget;

	//Widget To store the current GameUI
	class UUserWidget* CurrentGameWidget;

	//Called to set Pause UI
	bool PauseMenuIsOn;

	virtual void SetupInputComponent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AChar_PlayerController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Functions to handle movement of player
	UFUNCTION()
	virtual void MoveForward(float AxisValue);

	UFUNCTION()
	virtual void MoveRight(float AxisValue);

	//Function to pause the game and show UI
	UFUNCTION(BlueprintCallable)
	virtual void PauseGame();

	UFUNCTION()
	virtual void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> PauseWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> GameWidget;

	UFUNCTION(BlueprintPure)
	FRotator ReturnHipBoneRotation();

};
