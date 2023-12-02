// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class PROJECTLAMBDA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	#pragma region Properties
private:

	#pragma region Player Config
	UPROPERTY(EditAnywhere, Category="Player Config", meta=(DisplayName="Player Static Mesh"))
	class UStaticMeshComponent* PlayerStaticMesh;

	
	#pragma endregion

	#pragma region Input Mapping / Actions
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(DisplayName="Input Mapping Context"))
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, Category="Input", meta=(DisplayName="Move Input"))
	class UInputAction* MoveInput;

	UPROPERTY(EditAnywhere, Category="Input", meta=(DisplayName="Strafe Input"))
	UInputAction* StrafeInput;
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(DisplayName="Fire Input"))
	UInputAction* ShootInput;

	UPROPERTY(EditAnywhere, Category="Input", meta=(DisplayName="Dash Input"))
	UInputAction* DashInput;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* SwapWeaponInput;

	
	#pragma endregion

	//Health / Damage Component
	UPROPERTY(EditAnywhere, Category="Component")
	class UHealthComponent* HealthComponent;
	
	class APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category="Player Config", meta=(DisplayName="Rotation Speed"))
	float RotationSpeed = 10.f;


	//Dash config
	UPROPERTY(EditAnywhere, Category="Player Config", meta=(DisplayName="Launch Force"))
	float LaunchForce = 5.f;

	UPROPERTY(EditAnywhere, Category="Player Config", meta=(DisplayName="Dash Delay"))
	float DashDelay = 3.f;
	
	bool bLaunchOnce = true; //Flag the tells us whether the player can dash or not

	//Timer handle
	FTimerHandle DashTimeHandle;
	

	//Debug config
	UPROPERTY(EditAnywhere, Category="General", meta=(DisplayName="Debug Mode (Logs / Spheres)"))
	bool bIsDebug = false;
	
	const float SphereRadius = 25.f;
	const int SphereSegments = 12;

	
	#pragma region Weapons
	
	class AWeaponBase* CurrentWeapon;

	UPROPERTY(EditAnywhere, Category="Weapons", meta=(DisplayName="Weapon Position"))
	USceneComponent* WeaponPosition;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TSubclassOf<class AWeaponBase> PistolClass;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TSubclassOf<class AWeaponBase> ShotgunClass;

	TArray<AWeaponBase*> Weapons;

	int WeaponLength = 0;

	int WeaponIndex = 0;
	
	#pragma endregion

	#pragma region Player Stats

	UPROPERTY(EditAnywhere, Category="Player Stats")
	float MovementSpeed = 100.f;
	
	UPROPERTY(EditAnywhere, Category="Player Stats")
	float ShootSpeed = 100.f;
	
	UPROPERTY(EditAnywhere, Category="Player Stats")
	float DamageAmountStat = 10.f;
	
	#pragma endregion
	
	#pragma endregion 

	#pragma region Actions
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ResetDash();

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

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount,
		FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnHit(AActor* Player, AActor* Enemy, FVector NormalImpulse, const FHitResult& Hit);

	#pragma endregion
};
