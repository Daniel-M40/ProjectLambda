// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WormAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLAMBDA_API AWormAIController : public AAIController
{
	GENERATED_BODY()

public:
	explicit AWormAIController(FObjectInitializer const& ObjectInitializer);

	//Called when the controller possess a pawn
	virtual void OnPossess(APawn* InPawn) override;
};
