// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectLambda/Player/Weapons/WeaponBase.h"
#include "Shotgun.generated.h"

UCLASS()
class PROJECTLAMBDA_API AShotgun : public AWeaponBase
{
	GENERATED_BODY()

#pragma region Properties
	
private:
	UPROPERTY(EditAnywhere, Category = "Shotgun")
	int32 NumProjectiles = 3;

	UPROPERTY(EditAnywhere, Category = "Shotgun")
	float ConeSpreadAngle = 20.f;

#pragma endregion

#pragma region Actions
	
public:
	// Sets default values for this actor's properties
	AShotgun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire() override;

#pragma endregion
};
