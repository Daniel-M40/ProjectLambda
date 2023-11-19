// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
APistolProjectile::APistolProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Static mesh for the projectile
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	ProjectileMesh->SetSimulatePhysics(true);

	//Projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = Lifespan;


}

// Called when the game starts or when spawned
void APistolProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APistolProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

