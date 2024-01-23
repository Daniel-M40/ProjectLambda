// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class AProjectile;

UCLASS()
class PROJECTLAMBDA_API AWeaponBase : public AActor
{
	GENERATED_BODY()

#pragma region Properties

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WeaponMesh;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawn;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	float FireRate = 1.5f;

	UPROPERTY(EditAnywhere, Category="Combat")
	float ShotDamage = 10.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	float InitShotSpeed = 1300.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	float MaxShotSpeed = 1300.f;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	float ShotLifeSpan = 10.f;
	
	//Flag which determines whether we can shoot the weapon
	bool bCanFire = true;

	//Timer handle which allows us to add a timer to the shooting
	FTimerHandle FireRateTimerHandle;

protected:

	//Max ammo the weapon can have
	UPROPERTY(EditAnywhere)
	int MaxAmmo = 10;
	
	//Current ammo count
	UPROPERTY(EditAnywhere)
	int AmmoCount = 10;
	
public:
	bool bIsActive = true;

	
	
#pragma endregion

#pragma region Action
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void EnableShooting();
	
public:

	virtual void Fire() PURE_VIRTUAL(AWeaponBase::Fire);

	void EnableFireTimer();

	int IncreaseAmmo(int ammoCount);

	int DecreaseAmmo();

	int GetAmmo();
	
#pragma endregion
};
