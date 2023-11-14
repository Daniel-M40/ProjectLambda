// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"
#include "PistolProjectile.h"

// Sets default values
APistol::APistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PistolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pistol Mesh"));
	PistolMesh->SetupAttachment(RootComponent);
	PistolMesh->SetCollisionProfileName(TEXT("OverlapAll"));

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawn->SetupAttachment(PistolMesh);

}

// Called when the game starts or when spawned
void APistol::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APistol::Fire()
{
	if (ProjectileClass) // Checks the projectile has been set in the editor
	{
		FVector SpawnLoacation = ProjectileSpawn->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawn->GetComponentRotation();
		APistolProjectile* Bullet = GetWorld()->SpawnActor<APistolProjectile>(ProjectileClass, SpawnLoacation, SpawnRotation);
	}
}

