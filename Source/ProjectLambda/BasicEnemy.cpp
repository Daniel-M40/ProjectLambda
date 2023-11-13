// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"
#include "Math/Vector.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

#include "BasicEnemyAI.h"

// Sets default values
ABasicEnemy::ABasicEnemy()
{
	

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BasicEnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PAWN MESH"));
	BasicEnemyMesh->SetupAttachment(RootComponent);

	

}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector EnenmyLocation = GetActorLocation();
	
	Cast<ABasicEnemyAI>(Controller)->Test();
	

}

// Called to bind functionality to input
void ABasicEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

