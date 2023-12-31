﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.generated.h"

class ACoreGameMode;

UCLASS()
class PROJECTLAMBDA_API ABasePickUp : public AActor
{
	GENERATED_BODY()

#pragma region Properties

private:
	UPROPERTY(EditAnywhere, Category="Actor Mesh")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category="Sphere Collision")
	class USphereComponent* SphereComponent;

protected:
	ACoreGameMode* CoreGameMode;
	
#pragma endregion 

#pragma region Actions
	
public:
	// Sets default values for this actor's properties
	ABasePickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma endregion
	
};
