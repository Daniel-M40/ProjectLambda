// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileSpeedPowerUp.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"
#include "Player/Projectiles/Projectile.h"


void AProjectileSpeedPowerUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (CheckCurrencyAmount()) // check if there's enough currency
	{
		CoreGameMode->DecreaseCurrency(Cost); // decrease currency by cost

		Projectile->ProjectileMaxSpeed += IncreaseProjectileSpeed; // increase projectile max speed

		Destroy(); // destroy power up
	}
}
