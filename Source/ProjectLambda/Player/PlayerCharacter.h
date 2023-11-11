// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class APistol;

UCLASS()
class PROJECTLAMBDA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	#pragma region Player Config
	UPROPERTY(EditAnywhere, Category="Player Config", meta=(DisplayName="Player Static Mesh"))
	class UStaticMeshComponent* playerStaticMesh;

	
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

	#pragma endregion
	
	class APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category="Player Config", meta=(DisplayName="Rotation Speed"))
	float mRotationSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category="General", meta=(DisplayName="Debug Mode (Logs / Spheres)"))
	bool bIsDebug = false;

	const float SphereRadius = 25.f;
	const int SphereSegments = 12;
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TSubclassOf<APistol> StartingWeapon;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RotatePlayer(const FVector& LookAtTarget, const float RotateSpeed);
	
	void MoveHandler(const struct FInputActionValue& Value); //Handles movement forward and backwards
	
	void StrafeHandler(const FInputActionValue& Value); //Handles movement left and right
	
	void ShootHandler(const FInputActionValue& Value); //Handles the firing input

	void AttachWeapon(TSubclassOf<AActor> weaponClass, FName socketName);//Attaches a weapon class to the player
	
};
