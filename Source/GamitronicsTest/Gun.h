// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class GAMITRONICSTEST_API AGun : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Variable to hold the gun mesh
	UPROPERTY(EditDefaultsOnly, Category = "Gun Mesh")
	class UStaticMeshComponent* GunMesh;

	//Variable to point the position to spawn projectiles
	UPROPERTY(EditDefaultsOnly, Category = "Gun Barrel")
	class UArrowComponent* BarrelPointer;

public:	
	// Sets default values for this actor's properties
	AGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AProjectiles> ProjectileToSpawn;

	UFUNCTION(BlueprintCallable)
	void FireProjectile();

};
