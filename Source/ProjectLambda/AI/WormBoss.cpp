// Fill out your copyright notice in the Description page of Project Settings.


#include "WormBoss.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectLambda/Components/HealthComponent.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"

// Sets default values
AWormBoss::AWormBoss()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWormBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWormBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWormBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



UBehaviorTree* AWormBoss::GetBehaviorTree() const
{
	return Tree;
}



float AWormBoss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//If we have health component apply damage
	if (HealthComponent)
	{
		CurrentHealth = HealthComponent->ApplyDamage(DamageAmount, true);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AWormBoss::HandleDestruction()
{
	Super::HandleDestruction();
}

