// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

class ADoor;

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
		TSubclassOf<ADoor> DoorPrebuild;


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


private:

	class ARoomManager* Manager = nullptr;
	int GridHorizontal = 0;
	int GridVertical = 0;

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
		void SpawnDoors();

};
