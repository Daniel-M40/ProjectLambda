// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"

#include "ProjectLambda/Player/Projectiles/Projectile.h"


// Sets default values
AShotgun::AShotgun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShotgun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShotgun::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Shotgun Fired"));

	//If we have the projectile class and can fire spawn projectile
	if (ProjectileClass && bCanFire) // Checks the projectile has been set in the editor
	{
		for (int32 Index = 0; Index < NumProjectiles; Index++)
		{
			FVector SpawnLoacation = ProjectileSpawn->GetComponentLocation();
			FRotator SpawnRotation = ProjectileSpawn->GetComponentRotation();

			//Spawn projectile at projectile spawn location and rotation
			AProjectile* Bullet = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoacation, SpawnRotation);
			Bullet->SetProjectileStats(ShotDamage, InitShotSpeed, MaxShotSpeed, ShotLifeSpan);
			
			// Calculate spread angle and adjust projectile rotation here
			float SpreadAngle = ((float)Index / (float)(NumProjectiles - 1)) * ConeSpreadAngle - (ConeSpreadAngle / 2.0f);
			FRotator SpreadRotation = GetActorRotation() + FRotator(0.0f, SpreadAngle, 0.0f);

			Bullet->SetActorRotation(SpreadRotation);

			//Set the owner of the projectile
			Bullet->SetOwner(this);
		}
		


		EnableFireTimer();
	}
}

