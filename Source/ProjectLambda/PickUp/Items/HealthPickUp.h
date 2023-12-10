// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectLambda/PickUp/BasePickUp.h"
#include "HealthPickUp.generated.h"

UCLASS()
class PROJECTLAMBDA_API AHealthPickUp : public ABasePickUp
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHealthPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
