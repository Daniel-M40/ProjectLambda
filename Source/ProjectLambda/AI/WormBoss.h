// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "BaseEnemyCharacter.h"
#include "WormBoss.generated.h"


UCLASS()
class PROJECTLAMBDA_API AWormBoss : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWormBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;


	virtual void HandleDestruction();

	class ACoreGameMode* CoreGameMode;

	class UHealthComponent* HealthComponent;

	UBehaviorTree* GetBehaviorTree() const;




	UFUNCTION(BlueprintCallable)
	void Spit();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

private:
	UPROPERTY(EditAnywhere, Category="Attacks")
	TSubclassOf<class AProjectile> SpitProjectile;

	UPROPERTY(EditAnywhere, Category = "Attacks")
	int NumSpitLowerBound = 8;
	UPROPERTY(EditAnywhere, Category = "Attacks")
	int NumSpitUpperBound = 16;


	UPROPERTY(EditAnywhere, Category = "Attacks")
	TSubclassOf<class ABaseEnemyCharacter> EnemySpawn;
	
};
