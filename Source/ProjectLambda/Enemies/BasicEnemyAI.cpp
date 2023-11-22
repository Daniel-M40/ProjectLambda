// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemyAI.h"

ABasicEnemyAI::ABasicEnemyAI()
{
	SetActorTickEnabled(true);

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	RootComponent = ActorMesh;
	
}

void ABasicEnemyAI::BeginPlay()
{
	Super::BeginPlay();
}

void ABasicEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MoveTo(FVector(0, 0, 100.f));
}
