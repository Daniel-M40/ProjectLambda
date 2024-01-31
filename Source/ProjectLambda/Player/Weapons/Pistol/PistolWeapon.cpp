// Fill out your copyright notice in the Description page of Project Settings.

#include "PistolWeapon.h"
#include "ProjectLambda/Player/Projectiles/Projectile.h"
#include "Kismet/GameplayStatics.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
APistolWeapon::APistolWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APistolWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APistolWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APistolWeapon::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Pistol Fired"));

	//If we have the projectile class and can fire spawn projectile
	if (ProjectileClass && bCanFire) // Checks the projectile has been set in the editor
	{
		FVector SpawnLocation = ProjectileSpawn->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawn->GetComponentRotation();


		//Spawn projectile at projectile spawn location and rotation
		FTransform SpawnTransform = { SpawnRotation, SpawnLocation, FVector::OneVector };
		AActor* BulletActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);

		// Run before constructor
		//
		//    
		AProjectile* Bullet = Cast<AProjectile>(BulletActor);

		Bullet->SetProjectileStats(ShotDamage, InitShotSpeed, MaxShotSpeed, ShotLifeSpan);

		//Set the owner of the projectile
		Bullet->SetOwner(this);
		//
		// 
		// Run constructor
		UGameplayStatics::FinishSpawningActor(BulletActor, SpawnTransform);

		Super::Fire();
		EnableFireTimer();
	}

}

