// Fill out your copyright notice in the Description page of Project Settings.


#include "WormBoss.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectLambda/Components/HealthComponent.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"

#include "ProjectLambda/Player/Projectiles/Projectile.h"

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

void AWormBoss::Spit()
{

	// Get position and rotation of spawn socket
	FVector SpawnPosition = GetMesh()->GetSocketLocation("SpitSpawn");
	FRotator SpawnRotation = GetMesh()->GetSocketRotation("SpitSpawn");

	// Pick random number to spawn
	int toSpawn = FMath::RandRange(NumSpitLowerBound, NumSpitUpperBound);

	// Spawn that number of projectiles
	for (int i = 0; i < toSpawn; i++)
	{
		// Spawn in random direction
		SpawnRotation.Pitch = FMath::RandRange(60.f, 88.f);
		SpawnRotation.Yaw = FMath::RandRange(-180.f, 180.f);
		
		// Spawn the projectile
		AActor* Projectile = GetWorld()->SpawnActor<AProjectile>(SpitProjectile, SpawnPosition, SpawnRotation);
		Projectile->SetOwner(this);
	}
}

void AWormBoss::SpawnEnemy()
{
	// Spawn enemy at the socket
	GetWorld()->SpawnActor<ABaseEnemyCharacter>(EnemySpawn, GetMesh()->GetSocketLocation("EnemySpawn"), FRotator::ZeroRotator);
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
	ACoreGameMode* GameMode = Cast<ACoreGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	GameMode->EndGame(true);

	Super::HandleDestruction();
}

