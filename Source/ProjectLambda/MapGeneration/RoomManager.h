// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomManager.generated.h"

class ARoom;

USTRUCT()
struct FMapValue
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		int roomType;

	UPROPERTY(VisibleAnywhere)
		TArray<int> Doors;

	//UPROPERTY(VisibleAnywhere)
	//	int entranceDirection;

	//UPROPERTY(VisibleAnywhere)
	//	int exitDirection;
};


USTRUCT()
struct FMapRow
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		TArray<FMapValue> column;
};

USTRUCT()
struct FRoomMapRow
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere)
		TArray<ARoom*> column;
};


USTRUCT()
struct FIntVector2D
{
	GENERATED_BODY()

	int X;
	int Y;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLAMBDA_API ARoomManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ARoomManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Map Generation")
		TArray<TSubclassOf<ARoom>> RoomTypes;

	UPROPERTY(EditAnywhere, Category = "Map Generation")
		TSubclassOf<ARoom> BossRoomClass;
	const int BossRoomCode = -1;

	UPROPERTY(EditAnywhere, Category = "Map Generation")
		TSubclassOf<ARoom> StartRoomClass;
	const int StartRoomCode = -2;
		

	UPROPERTY(EditAnywhere, Category = "Map Generation")
		int mapHeight = 8; // Max number of rooms north/south
	UPROPERTY(EditAnywhere, Category = "Map Generation")
		int mapWidth = 8; // Max number of rooms east/west

	UPROPERTY(EditAnywhere, Category = "Map Generation")
		float roomInterval = 500.f; // Interval between room centres



	UPROPERTY(EditAnywhere, Category = "Map Generation")
		int roomsToBoss = 8; // Number of rooms to generate before boss is reached


	UPROPERTY(EditAnywhere, Category = "Map Generation")
		int numberOfBranches = 3;

	UPROPERTY(EditAnywhere, Category = "Map Generation")
		int branchMaxLength = 3;



	UPROPERTY()
		FIntVector2D start;

	// 2-Dimensional array storing the type of room at each location
	// 0 means no room

	UPROPERTY(VisibleAnywhere, Category = "Map Generation")
		TArray<FMapRow> map;

	UPROPERTY(VisibleAnywhere, Category = "Map Generation")
		TArray<FRoomMapRow> roomMap;

	UPROPERTY(VisibleAnywhere, Category = "Map Generation")
		ARoom* StartRoom = nullptr;
public:

	UFUNCTION()
		ARoom* GetRoomAt(int Horizontal, int Vertical);

	UFUNCTION()
		bool GenerateMap();

	UFUNCTION()
		bool GenerateRooms();
};

