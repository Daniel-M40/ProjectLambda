// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyCharacter.h"
#include "FastEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLAMBDA_API AFastEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()
private:


public:
	// Sets default values for this character's properties
	AFastEnemyCharacter();

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

};
