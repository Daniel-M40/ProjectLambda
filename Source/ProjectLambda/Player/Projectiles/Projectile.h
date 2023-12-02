// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PROJECTLAMBDA_API AProjectile : public AActor
{
	GENERATED_BODY()

#pragma region Properties

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta = (DisplayName = "Projectile Mesh", AllowPrivateAccess = true))
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (DisplayName = "Initial Speed", AllowPrivateAccess = true))
	float ProjecitleInitialSpeed = 1300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (DisplayName = "Max Speed", AllowPrivateAccess = true))
	float ProjectileMaxSpeed = 1300.f;
	
	
	
	UPROPERTY(EditAnywhere)
	float Lifespan = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "Movement", meta = (DisplayName = "Projectile Mesh"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;
	
#pragma endregion

#pragma region Actions
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& HitResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

#pragma endregion

};
