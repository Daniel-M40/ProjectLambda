// Fill out your copyright notice in the Description page of Project Settings.


#include "BossRoom.h"
#include "../AI/WormBoss.h"

// Called every frame
void ABossRoom::Tick(float DeltaTime)
{
	Super::Super::Tick(DeltaTime);
}


void ABossRoom::Activate()
{
	SetDoorsActive(false);

	FVector SpawnPos = GetActorLocation();

	GetWorld()->SpawnActor<ABaseEnemyCharacter>(BossToSpawn, SpawnPos, FRotator::ZeroRotator);
}

