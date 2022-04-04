// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Char_Player.h"

// Sets default values
AProjectiles::AProjectiles() : SphereCollider(NULL), SphereMesh(NULL), ProjectileDamagePower(20)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating the projectile mesh and collider
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	RootComponent = SphereCollider;
	SphereCollider->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	SphereCollider->SetNotifyRigidBodyCollision(true);

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetupAttachment(RootComponent);
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->InitialSpeed = 1200.0f;
		ProjectileMovementComponent->MaxSpeed = 1500.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
}

// Called when the game starts or when spawned
void AProjectiles::BeginPlay()
{
	Super::BeginPlay();

	SphereCollider->OnComponentHit.AddDynamic(this, &AProjectiles::OnHit);
	
}

// Called every frame
void AProjectiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectiles::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AChar_Player* OverlappedEnemy = Cast<AChar_Player>(OtherActor);
	if (OverlappedEnemy)
	{
		OverlappedEnemy->ApplyHealthDamage(ProjectileDamagePower);
	}
	Destroy();
}


