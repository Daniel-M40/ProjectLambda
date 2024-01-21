// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectLambda/PickUp/BasePickUp.h"
#include "CurrencyPickUp.generated.h"

UCLASS()
class PROJECTLAMBDA_API ACurrencyPickUp : public ABasePickUp
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ACurrencyPickUp();

	UPROPERTY(EditAnywhere)
	int CurrencyIncrease = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	//Game mode ref
	ACoreGameMode* CoreGameMode;

};
