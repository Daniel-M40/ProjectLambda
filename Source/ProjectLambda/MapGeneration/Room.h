// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

class ADoor;
class ABaseEnemyCharacter;

UCLASS()
class PROJECTLAMBDA_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	int entrancedoor;

	UPROPERTY(VisibleAnywhere)
	int exitdoor;


private:

	// Can there be doors in these locations?
	// Reference to the door

	UPROPERTY(EditAnywhere)
		TSubclassOf<ADoor> DoorClass;


	UPROPERTY(EditAnywhere)
		bool canDoorNorth = true;
	UPROPERTY(VisibleAnywhere)
		bool isDoorNorth = false;
	UPROPERTY(EditAnywhere)
		USceneComponent* DoorNorthSpawn;
		ADoor* DoorNorth;

	UPROPERTY(EditAnywhere)
		bool canDoorEast = true;
	UPROPERTY(VisibleAnywhere)
		bool isDoorEast = false;
	UPROPERTY(EditAnywhere)
		USceneComponent* DoorEastSpawn;
		ADoor* DoorEast;

	UPROPERTY(EditAnywhere)
		bool canDoorSouth = true;
	UPROPERTY(VisibleAnywhere)
		bool isDoorSouth = false;
	UPROPERTY(EditAnywhere)
		USceneComponent* DoorSouthSpawn;
		ADoor* DoorSouth;

	UPROPERTY(EditAnywhere)
		bool canDoorWest = true;
	UPROPERTY(VisibleAnywhere)
		bool isDoorWest = false;
	UPROPERTY(EditAnywhere)
		USceneComponent* DoorWestSpawn;
		ADoor* DoorWest;

	UPROPERTY(EditAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "Enemy Spawning")
		bool bIsActive;
	UPROPERTY(VisibleAnywhere, Category = "Enemy Spawning")
		bool bIsComplete;


	UPROPERTY(VisibleAnywhere, Category = "Enemy Spawning")
		FVector RoomOrigin; // Where is the room origin?
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
		FVector RoomBounds; // How large is the room? Used to calculate where is offscreen

	UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
		int RemainingEnemies = 0; // How many enemies should be spawned?

	UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
		float TimeToSpawn = 10.f; // How long it should take to spawn the enemies

	float SpawnTimer = 0;
	float SpawnInterval = 5.f; // Time between spawns

	UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
		float SpawnPositionBuffer = 100.f; // How long it should take to spawn the enemies

	float CameraSizeX;
	float CameraSizeY;

	UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
		TSubclassOf<ABaseEnemyCharacter> EnemyClass;

	UFUNCTION()
		FVector GenerateEnemySpawnPos();

private:

	class ARoomManager* Manager = nullptr;
	int GridHorizontal = 0;
	int GridVertical = 0;

	UFUNCTION()
		void CalculateCameraSize();

public:
	// Spawn the room
	// Enable/disable doors
	// Returns true if successful
	UFUNCTION()
		bool SetDoor(int direction, bool isDoor);

	UFUNCTION()
		ADoor* GetDoor(int direction);

	// ----- Maybe add difficulty multiplier for later levels? -----
	// ----- Could effect spawnrate/health of enemies -----
	//bool SetDifficulty(float difficulty);

	// Set the array coordinates of the room
	UFUNCTION()
		void Setup(ARoomManager* _Manager, int _GridHorizontal , int _GridVertical);

	UFUNCTION()
		void GetCoords(int& horizontal, int& vertical);

	UFUNCTION()
		ARoomManager* GetManager();

	UFUNCTION()
		void Activate();

	UFUNCTION()
		void Complete();

	ADoor* SpawnDoor(USceneComponent* DoorSpawn, int direction);
	
	UFUNCTION()
		void SpawnDoors();

	UFUNCTION()
		void SetDoorsActive(bool doorsActive);
};
