// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectLambda/Player/Weapons/WeaponBase.h"
#include "PistolWeapon.generated.h"

UCLASS()
class PROJECTLAMBDA_API APistolWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APistolWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire() override;
};
