// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectLambda/PickUp/BasePowerUp.h"
#include "HealthIncrease.generated.h"

UCLASS()
class PROJECTLAMBDA_API AHealthIncrease : public ABasePowerUp
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Config")
	float MaxHealthIncrease = 10.f;

public:
	// Sets default values for this actor's properties
	AHealthIncrease();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
