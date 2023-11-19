// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PistolProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class PROJECTLAMBDA_API APistolProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APistolProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
	float Lifespan = 10.0f;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovement;


};
