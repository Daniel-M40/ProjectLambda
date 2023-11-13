// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicEnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLAMBDA_API ABasicEnemyAI : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Properties")
	UStaticMeshComponent* ActorMesh;
	
public:
	ABasicEnemyAI();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};
