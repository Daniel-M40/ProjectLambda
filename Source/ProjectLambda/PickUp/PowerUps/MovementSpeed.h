// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectLambda/PickUp/BasePowerUp.h"
#include "MovementSpeed.generated.h"

UCLASS()
class PROJECTLAMBDA_API AMovementSpeed : public ABasePowerUp
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Config")
	float MovementSpeedIncrease = 100.f;

public:
	// Sets default values for this actor's properties
	AMovementSpeed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
