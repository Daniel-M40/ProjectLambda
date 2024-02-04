// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectLambda/Components/HealthComponent.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Static mesh for the player
	//Unneeded once using character mesh from character class
	//characterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Character Static Mesh"));
	//characterMesh->SetupAttachment(RootComponent);
	
	//fires event when player collides with another actor
	//characterMesh->SetNotifyRigidBodyCollision(true);

	//Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	
}

// Called when the game starts or when spawned
void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	
	//Get game mode ref
	CoreGameMode = Cast<ACoreGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* ABaseEnemyCharacter::GetBehaviorTree() const
{
	return Tree;
}

float ABaseEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//If we have health component apply damage
	if (HealthComponent)
	{
		CurrentHealth = HealthComponent->ApplyDamage(DamageAmount, true);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABaseEnemyCharacter::HandleDestruction()
{
	//@@TODO Play sound and particle effects here

	
	
	if (CoreGameMode)
	{
		//Spawn pickup at enemy death location
		CoreGameMode->SpawnPickUp(GetActorLocation(), GetActorRotation());
	}
	
	Destroy();
}

