// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileDamagePowerUp.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"
#include "Player/Projectiles/Projectile.h"

void AProjectileDamagePowerUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CheckCurrencyAmount()) // check if there's enough currency
	{
		CoreGameMode->DecreaseCurrency(Cost); // decrease currency based on price

		Projectile->ProjectileDamage += IncreaseProjectileDamage; // increase projectile damage

		Destroy(); // destroy power up
	}
}
