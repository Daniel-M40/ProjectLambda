// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "BaseEnemyCharacter.generated.h"

UCLASS()
class PROJECTLAMBDA_API ABaseEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Character Config", meta = (DisplayName = "Static Mesh"))
	class UStaticMeshComponent* characterMesh;

	//Health / Damage Component
	UPROPERTY(EditAnywhere, Category="Component")
	class UHealthComponent* HealthComponent;

public:
	UPROPERTY(EditAnywhere, Category="Combat")
	float OnCollideDamage = 10.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	bool bDamageOnCollide = true;
	
public:
	// Sets default values for this character's properties
	ABaseEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Character Config")
	UBehaviorTree* Tree;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTree() const;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	
	virtual void HandleDestruction();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

	class ACoreGameMode* CoreGameMode;

};
