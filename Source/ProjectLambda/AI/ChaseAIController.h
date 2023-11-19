// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ChaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLAMBDA_API AChaseAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	explicit AChaseAIController(FObjectInitializer const &ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

};
