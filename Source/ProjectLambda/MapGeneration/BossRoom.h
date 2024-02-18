// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "BossRoom.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLAMBDA_API ABossRoom : public ARoom
{
	GENERATED_BODY()

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category="Boss")
	TSubclassOf<class ABaseEnemyCharacter> BossToSpawn;

public:
	virtual void Activate();
};
