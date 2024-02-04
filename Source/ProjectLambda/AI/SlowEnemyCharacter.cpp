// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowEnemyCharacter.h"

#include "BaseEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectLambda/Components/HealthComponent.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"

// Sets default values
ASlowEnemyCharacter::ASlowEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	

}

// Called when the game starts or when spawned
void ASlowEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

	//Get game mode ref
	CoreGameMode = Cast<ACoreGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void ASlowEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlowEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* ASlowEnemyCharacter::GetBehaviorTree() const
{
	return Tree;
}



float ASlowEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//If we have health component apply damage
	if (HealthComponent)
	{
		CurrentHealth = HealthComponent->ApplyDamage(DamageAmount, true);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ASlowEnemyCharacter::HandleDestruction()
{
	//@@TODO Play sound and particle effects here

	//Spawn pickup at enemy death location
	//CoreGameMode->SpawnPickup(GetActorLocation(), GetActorRotation());

	Destroy();
}