// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectLambda/PickUp/BasePickUp.h"
#include "BasePowerUp.generated.h"

UCLASS()
class PROJECTLAMBDA_API ABasePowerUp : public ABasePickUp
{
	GENERATED_BODY()

#pragma region Properties

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Cost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Title = "Power Up";
	
#pragma endregion 

public:
	// Sets default values for this actor's properties
	ABasePowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool CheckCurrencyAmount();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
