// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp/BasePowerUp.h"
#include "ProjectileDamagePowerUp.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLAMBDA_API AProjectileDamagePowerUp : public ABasePowerUp
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float IncreaseProjectileDamage = 10.f;

public:

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
