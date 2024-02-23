// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Kismet/GameplayStatics.h"
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
	DecreaseAmmo();
}

void AWeaponBase::PlayOutOfAmmoSound()
{
	//Play out of ammo sound
	if (OutOfAmmoSound)
	{
		//Play door sound
		UGameplayStatics::PlaySoundAtLocation(this, OutOfAmmoSound, GetActorLocation(),
			OutOfAmmoSoundVolume, OutOfAmmoSoundPitch);
	}
}

void AWeaponBase::EnableFireTimer()
{
	//After firing set flag to false to prevent user from shooting again until timer resets flag
	bCanFire = false;
	
	if (FireSound)
	{
		//Play door sound
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation(),
			FireSoundVolume, FireSoundPitch);
	}
	
	//Timer to delay the shooting
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AWeaponBase::EnableShooting, FireRate, false);
}

int AWeaponBase::IncreaseAmmo(int ammoCount)
{
	//If we have less ammo than ammo count the increase ammo
	if (AmmoCount < MaxAmmo)
	{
		AmmoCount += ammoCount;

		//if new ammo total is above the max ammo count set it to the max ammo count
		if (AmmoCount >= MaxAmmo)
		{
			AmmoCount = MaxAmmo;
		}
	}

	return AmmoCount;
}

int AWeaponBase::DecreaseAmmo()
{
	if (AmmoCount > 0)
	{
		AmmoCount--; // decrease ammo when player shoots
	}
	
	return AmmoCount;
}

int AWeaponBase::GetAmmo()
{
	return AmmoCount;
}



