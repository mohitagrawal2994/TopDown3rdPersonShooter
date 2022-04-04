// Fill out your copyright notice in the Description page of Project Settings.


#include "Char_PlayerController.h"
#include "Components/InputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Char_Player.h"


AChar_PlayerController::AChar_PlayerController() : MouseWorldLocation(0), MouseWorldDirection(0), BoneNewRot(0), CharPlayer(NULL), CurrentPauseWidget(NULL), CurrentGameWidget(NULL), PauseMenuIsOn(false), PauseWidget(NULL)
{

}

// Called when the game starts or when spawned
void AChar_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Get Current Controlled Pawn
	CharPlayer = Cast<AChar_Player>(GetPawn());

	//If Widget is assigned in blueprint create a new widget
	if (PauseWidget != NULL)
	{
		CurrentPauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidget);
	}

	if (GameWidget != NULL)
	{
		CurrentGameWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidget);
		CurrentGameWidget->AddToViewport();
	}

	//Set Show Mouse Cursor to true
	bShowMouseCursor = true;
	
}

// Called every frame
void AChar_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CharPlayer != NULL)
	{
		//Setting the mesh to face the mouse position
		DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
		BoneNewRot = FRotator(CharPlayer->GetActorRotation().Pitch, MouseWorldDirection.Rotation().Yaw, CharPlayer->GetActorRotation().Roll);
		CharPlayer->GetMesh()->SetRelativeRotation(BoneNewRot);
	}
}


void AChar_PlayerController::SetupInputComponent()
{
	/*PlayerInputComponent = NewObject<UInputComponent>(this, TEXT("PC_InputComponent0"));
	PlayerInputComponent->RegisterComponent();*/

	Super::SetupInputComponent();

	//Binding Movement Functions
	InputComponent->BindAxis("MoveForward", this, &AChar_PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AChar_PlayerController::MoveRight);

	//Binding Pause Button Function
	InputComponent->BindAction("PauseGame", IE_Pressed, this, &AChar_PlayerController::PauseGame);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AChar_PlayerController::Fire);
}

void AChar_PlayerController::MoveForward(float AxisValue)
{
	if (CharPlayer != NULL)
	{
		CharPlayer->MoveForward(AxisValue);
	}
}

void AChar_PlayerController::MoveRight(float AxisValue)
{
	if (CharPlayer != NULL)
	{
		CharPlayer->MoveRight(AxisValue);
	}
}

void AChar_PlayerController::PauseGame()
{
	//If PlayerController and Widget Exist DO
	if (CurrentPauseWidget != NULL)
	{
		//Logic to toggle the Pause Menu UI
		if (PauseMenuIsOn)
		{
			//Setting Game Mode and GameState
			SetInputMode(FInputModeGameOnly());
			SetPause(false);

			//Remove widget from screen
			CurrentPauseWidget->RemoveFromViewport();
			CurrentGameWidget->AddToViewport();
			PauseMenuIsOn = false;
		}
		else
		{
			//Setting Game Mode and GameState
			SetInputMode(FInputModeUIOnly());
			SetPause(true);

			//Add widget from screen
			CurrentPauseWidget->AddToViewport();
			CurrentGameWidget->RemoveFromViewport();
			PauseMenuIsOn = true;
		}
	}
}

void AChar_PlayerController::Fire()
{
	CharPlayer->FireGun();
}

FRotator AChar_PlayerController::ReturnHipBoneRotation()
{
	return BoneNewRot;
}
