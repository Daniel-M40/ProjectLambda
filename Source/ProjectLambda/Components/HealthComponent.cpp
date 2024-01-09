// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectLambda/AI/BaseEnemyCharacter.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"
#include "ProjectLambda/Player/PlayerCharacter.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	//Get game mode ref
	CoreGameMode = Cast<ACoreGameMode>(UGameplayStatics::GetGameMode(this));
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

float UHealthComponent::ApplyDamage(float DamageDealt, bool bIsEnemy)
{

	//Deal damage
	CurrentHealth -= DamageDealt;

	//Get owner
	AActor* Owner = GetOwner();

	APlayerCharacter* Player = Cast<APlayerCharacter>(Owner);
	ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(Owner);
	
	//Check if owner is dead
	if (CurrentHealth <= 0.f)
	{
		if (Owner)
		{
			//Check if the actor that has died is a the player or an enemy
			if (bIsEnemy)
			{
				Enemy->HandleDestruction();
			}
			else
			{
				Player->HandleDestruction();
			}
		}
	}

	return CurrentHealth;
}

void UHealthComponent::IncreaseHealth(float HealthIncrease)
{
	//Increase health if we are not at the max health
	if (CurrentHealth < MaxHealth)
	{
		CurrentHealth += HealthIncrease;
	}
}

