// Fill out your copyright notice in the Description page of Project Settings.


#include "FastEnemyCharacter.h"

#include "BaseEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectLambda/Components/HealthComponent.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"

// Sets default values
AFastEnemyCharacter::AFastEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;





}

// Called when the game starts or when spawned
void AFastEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

	//Get game mode ref
	CoreGameMode = Cast<ACoreGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void AFastEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFastEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* AFastEnemyCharacter::GetBehaviorTree() const
{
	return Tree;
}



float AFastEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//If we have health component apply damage
	if (HealthComponent)
	{
		CurrentHealth = HealthComponent->ApplyDamage(DamageAmount, true);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AFastEnemyCharacter::HandleDestruction()
{
	Super::HandleDestruction();
}

