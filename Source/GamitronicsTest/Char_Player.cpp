// Fill out your copyright notice in the Description page of Project Settings.


#include "Char_Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Gun.h"

// Sets default values
AChar_Player::AChar_Player() : bIsDead(false), Health(100.0f), Ammo(100), Rage(75.0f), SpringArm(NULL), PlayerCamera(NULL)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating the spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	//Creating the player camera component
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AChar_Player::BeginPlay()
{
	Super::BeginPlay();

	if (GunToSpawn != NULL)
	{
		FActorSpawnParameters SpawnParams;
		SpawnedGun = Cast<AGun>(GetWorld()->SpawnActor<AActor>(GunToSpawn, GetMesh()->GetSocketTransform(TEXT("Gun Socket")), SpawnParams));

		if (SpawnedGun != NULL)
		{
			SpawnedGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, TEXT("Gun Socket"));
		}
		
	}
}

// Called every frame
void AChar_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AChar_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AChar_Player::MoveForward(float AxisValue)
{
	if (AxisValue != 0)
	{
		AddMovementInput(GetActorForwardVector(), AxisValue);
	}
}

void AChar_Player::MoveRight(float AxisValue)
{
	if (AxisValue != 0)
	{
		AddMovementInput(GetActorRightVector(), AxisValue);
	}
}

void AChar_Player::FireGun()
{
	if (Ammo > 0)
	{
		Ammo = Ammo - 1;
		SpawnedGun->FireProjectile();
	}	
}

float AChar_Player::ReturnHealth()
{
	return Health;
}

int AChar_Player::ReturnAmmo()
{
	return Ammo;
}

float AChar_Player::ReturnRage()
{
	return Rage;
}

bool AChar_Player::ReturnIsDead()
{
	return bIsDead;
}

void AChar_Player::ApplyHealthDamage(int DamageAmount)
{
	Health = Health - DamageAmount;
	if (Health < 0)
	{
		bIsDead = true;

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SpawnedGun->SetLifeSpan(3.0f);
		SetLifeSpan(3.0f);	
	}
}
