﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"

#include "ProjectLambda/Player/Projectiles/Projectile.h"


// Sets default values
APistol::APistol()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	Super::Fire();
	UE_LOG(LogTemp, Warning, TEXT("Pistol Fired"));

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

