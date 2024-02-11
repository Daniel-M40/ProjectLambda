// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "PlayerCharacter.generated.h"

class AProjectLambdaGameModeBase;

UCLASS()
class PROJECTLAMBDA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:

#pragma region Player Config
	// Unneeded after implementing skeletal mesh
	//UPROPERTY(EditAnywhere, Category = "Player Config", meta = (DisplayName = "Player Static Mesh"))
	//class UStaticMeshComponent* PlayerStaticMesh;


#pragma endregion

#pragma region Input Mapping / Actions

	UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Input Mapping Context"))
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Move Input"))
	class UInputAction* MoveInput;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Strafe Input"))
	UInputAction* StrafeInput;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Fire Input"))
	UInputAction* ShootInput;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Dash Input"))
	UInputAction* DashInput;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SwapWeaponInput;


#pragma endregion

	//Health / Damage Component
	UPROPERTY(EditAnywhere, Category = "Component")
	class UHealthComponent* HealthComponent;

	float MaxHealth = 30.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	int MaxAmmo = 20;

	class APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category = "Player Config", meta = (DisplayName = "Rotation Speed"))
	float RotationSpeed = 10.f;


	//Dash config
	UPROPERTY(EditAnywhere, Category = "Player Config", meta = (DisplayName = "Launch Force"))
	float LaunchForce = 5.f;

	UPROPERTY(EditAnywhere, Category = "Player Config", meta = (DisplayName = "Dash Delay"))
	float DashDelay = 3.f;

	bool bLaunchOnce = true; //Flag the tells us whether the player can dash or not

	//Timer handle for the players dash
	FTimerHandle DashTimeHandle;

	//Handle for players invincibility after being damaged
	FTimerHandle InvincibleTimeHandle;
	
	//Components
	class UCharacterMovementComponent* MovementComponent;
	

	UPROPERTY(EditAnywhere, Category="Player Config")
	float InvincibleTime = 3.f;
	
	//Flag to show whether the player is currently invincible or not
	bool bIsInvincible = false;

	//Game mode ref
	class ACoreGameMode* CoreGameMode;
	
	//Debug config
	UPROPERTY(EditAnywhere, Category = "General", meta = (DisplayName = "Debug Mode (Logs / Spheres)"))
	bool bIsDebug = false;

	const float SphereRadius = 25.f;
	const int SphereSegments = 12;


#pragma region Weapons


	FName weaponSocket;

	UPROPERTY(EditAnywhere, Category = "Weapons", meta = (DisplayName = "Weapon Socket"))
	class AWeaponBase* CurrentWeapon;

	UPROPERTY(EditAnywhere, Category = "Weapons", meta = (DisplayName = "Weapon Position"))
	USceneComponent* WeaponPosition;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TSubclassOf<class AWeaponBase> PistolClass;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TSubclassOf<class AWeaponBase> ShotgunClass;

	TArray<AWeaponBase*> Weapons;

	int WeaponLength = 0;

	int WeaponIndex = 0;

#pragma endregion

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

	//Value so we can display the ammo, NOT THE ACTUAL AMMO VALUE FOR THE WEAPON
	//Go to the weapon class for the actual ammo value
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Ammo = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAlive = true;

	// Value only for displaying currency
	//Go to CoreGameMode for actual currency
	UPROPERTY(EditAnywhere)
	int Currency = 0;

	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 1.f;
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	UFUNCTION()
	void OnHit(AActor* Player, AActor* Enemy, FVector NormalImpulse, const FHitResult& Hit);

	virtual void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ResetDash();

	void DisableInvincibility();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Input Handles
	void RotatePlayer(const FVector& LookAtTarget, const float RotateSpeed);

	void MoveHandler(const struct FInputActionValue& Value); //Handles movement forward and backwards

	void StrafeHandler(const FInputActionValue& Value); //Handles movement left and right

	void ShootHandler(const FInputActionValue& Value); //Handles the firing input

	void SwapWeaponHandler(const FInputActionValue& Value);

	//Handles dash input
	void DashHandler(const FInputActionValue& Value);

#pragma endregion

	//Attaches a weapon class to the player
	void AttachWeapon();

	//Increase ammo for weapons
	void IncreaseShotgunAmmo(float ammoIncrease);

	//Health component functions
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount,
		FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void IncreaseHealth(float healthIncrement);
	
	void IncreaseMaxHealth(float healthIncrement);

};

