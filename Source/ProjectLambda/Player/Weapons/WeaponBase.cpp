// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "ProjectLambda/Player/Projectiles/Projectile.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponMesh->SetCollisionProfileName(TEXT("OverlapAll"));

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawn->SetupAttachment(WeaponMesh);

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Fire()
{
	if (ProjectileClass) // Checks the projectile has been set in the editor
	{
		FVector SpawnLoacation = ProjectileSpawn->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawn->GetComponentRotation();

		//Spawn projectile at projectile spawn location and rotation
		AProjectile* Bullet = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoacation, SpawnRotation);

		//Set the owner of the projectile
		Bullet->SetOwner(this);
	}
}

