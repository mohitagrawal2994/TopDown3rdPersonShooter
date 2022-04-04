// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectiles.h"

// Sets default values
AGun::AGun() : GunMesh(NULL), BarrelPointer(NULL)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating the gun mesh
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	RootComponent = GunMesh;

	//Creating the arrow component
	BarrelPointer = CreateDefaultSubobject<UArrowComponent>(TEXT("BarrelPointer"));
	BarrelPointer->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::FireProjectile()
{
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(ProjectileToSpawn, BarrelPointer->GetComponentTransform(), SpawnParams);
}

