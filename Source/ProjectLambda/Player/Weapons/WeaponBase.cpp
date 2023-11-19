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

void AWeaponBase::EnableShooting()
{
	bCanFire = true;
}

void AWeaponBase::Fire()
{
}

void AWeaponBase::EnableFireTimer()
{
	//After firing set flag to false to prevent user from shooting again until timer resets flag
	bCanFire = false;
	
	//Timer to delay the shooting
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AWeaponBase::EnableShooting, FireRate, false);
}

