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
	
	UPROPERTY(EditAnywhere, Category="Config")
	float FireRate = 1.5f;
	
	//Flag which determines whether we can shoot the weapon
	bool bCanFire = true;

	//Timer handle which allows us to add a timer to the shooting
	FTimerHandle FireRateTimerHandle;

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

	virtual void Fire();

	void EnableFireTimer();
	
#pragma endregion
};
