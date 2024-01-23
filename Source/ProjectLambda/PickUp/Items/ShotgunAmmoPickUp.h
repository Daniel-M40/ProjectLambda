// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectLambda/PickUp/BasePickUp.h"
#include "ShotgunAmmoPickUp.generated.h"

UCLASS()
class PROJECTLAMBDA_API AShotgunAmmoPickUp : public ABasePickUp
{
	GENERATED_BODY()

#pragma region Properties

	UPROPERTY(EditAnywhere)
	int AmmoIncrease = 3;
	
#pragma endregion

public:
	// Sets default values for this actor's properties
	AShotgunAmmoPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
