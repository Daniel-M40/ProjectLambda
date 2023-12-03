// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "Door.h"
#include "RoomManager.h"

#include "../AI/BaseEnemyCharacter.h"

#include "NavigationSystem.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Room Origin"));
	RootComponent = Root;

	DoorNorthSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Door Spawn (North)"));
	DoorNorthSpawn->SetupAttachment(Root);
	DoorNorthSpawn->SetRelativeLocation(FVector(0, 250.f, 0));
	DoorNorthSpawn->AddRelativeRotation(FRotator(0, 180.f, 0));

	DoorEastSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Door Spawn (East)"));
	DoorEastSpawn->SetupAttachment(Root);
	DoorEastSpawn->SetRelativeLocation(FVector(250.f, 0, 0));
	DoorEastSpawn->AddRelativeRotation(FRotator(0, 90.f, 0));

	DoorSouthSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Door Spawn (South)"));
	DoorSouthSpawn->SetupAttachment(Root);
	DoorSouthSpawn->SetRelativeLocation(FVector(0, -250.f, 0));
	DoorSouthSpawn->AddRelativeRotation(FRotator(0, 0, 0));

	DoorWestSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Door Spawn (West)"));
	DoorWestSpawn->SetupAttachment(Root);
	DoorWestSpawn->SetRelativeLocation(FVector(-250.f, 0, 0));
	DoorWestSpawn->AddRelativeRotation(FRotator(0, -90.f, 0));

}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < DoorArrSize; i++)
	{
		ADoor* door = GetWorld()->SpawnActor<ADoor>();
		
		Doors.Add(door);
	}

	SpawnPoints.Add(DoorNorthSpawn);
	SpawnPoints.Add(DoorEastSpawn);
	SpawnPoints.Add(DoorWestSpawn);
	SpawnPoints.Add(DoorSouthSpawn);
	
	//GetActorBounds(false, RoomOrigin, RoomBounds);
	
	//GetActorBounds(false, RoomOrigin, RoomBounds);
	RoomOrigin = GetActorLocation();
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsActive)
	{
		if (RemainingEnemies > 0)
		{
			SpawnTimer += DeltaTime;

			while (SpawnTimer >= SpawnInterval)
			{
				SpawnTimer -= SpawnInterval;

				// Spawn the enemy
				UE_LOG(LogTemp, Warning, TEXT("Spawning Enemy"))
				GetWorld()->SpawnActor<ABaseEnemyCharacter>(EnemyClass, GenerateEnemySpawnPos(), FRotator::ZeroRotator);

				RemainingEnemies--;
			}
		}
		else
		{
			Complete();
		}
	}
}


FVector ARoom::GenerateEnemySpawnPos()
{
	// Choose random door to spawn from
	FVector SpawnPos = FVector::ZeroVector;
	do
	{
		int SpawnDoor = FMath::RandRange(0, 3);
		
		switch (SpawnDoor)
		{
		case 0:
			if (isDoorNorth)
				SpawnPos = Doors[0]->GetExitPosition()->GetComponentLocation();
			break;

		case 1:
			if (isDoorEast)
				SpawnPos = Doors[1]->GetExitPosition()->GetComponentLocation();
			break;

		case 2:
			if (isDoorSouth)
				SpawnPos = Doors[2]->GetExitPosition()->GetComponentLocation();
			break;

		case 3:
			if (isDoorWest)
				SpawnPos = Doors[3]->GetExitPosition()->GetComponentLocation();
			break;
		}
	} while (SpawnPos == FVector::ZeroVector);

	return SpawnPos;
}

void ARoom::CalculateCameraSize()
{
	float FOV = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetFOVAngle();
	float Opposite = FMath::Atan(FOV) * GetActorLocation().Z;

	CameraSizeX = Opposite;
	
	// Can't think of a good way to get Y, enemies will just spawn further away on this axis
	CameraSizeY = Opposite;
}

void ARoom::SetDoor(int direction)
{
	switch (direction)
	{
	case 0:
		isDoorNorth = true;
		break;
	case 1:
		isDoorEast = true;
		break;
	case 2:
		isDoorSouth = true;
		break;
	case 3:
		isDoorWest = true;
		break;
	}
}

ADoor* ARoom::GetDoor(int direction)
{
	ADoor* door = nullptr;
	
	door = Doors[direction];
	
	return door;
}


void ARoom::Setup(ARoomManager* _Manager, int _GridHorizontal, int _GridVertical)
{
	Manager = _Manager;

	GridHorizontal = _GridHorizontal;
	GridVertical = _GridVertical;
}

void ARoom::GetCoords(int& horizontal, int& vertical)
{
	horizontal = GridHorizontal;
	vertical = GridVertical;
}

ARoomManager* ARoom::GetManager()
{
	return Manager;
}

ADoor* ARoom::SpawnDoor(USceneComponent* DoorSpawn, int direction)
{
	ADoor* door = GetWorld()->SpawnActor<ADoor>(DoorClass, DoorSpawn->GetComponentLocation(), DoorSpawn->GetComponentRotation());
	
	door->AttachToComponent(DoorSpawn, FAttachmentTransformRules::KeepWorldTransform);
	door->Setup(this, direction);

	return door;
}

void ARoom::SpawnDoors()
{
	if (DoorClass)
	{
		// If should spawn a door at this direction
		// Spawn the door blueprint
		// Parent it to the door spawn position
		// Run the setup function to set door variables (parent room, direction)

		if (isDoorNorth)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Spawning North Door"))
			Doors[0] = SpawnDoor(DoorNorthSpawn, 0);

		}
		if (isDoorEast)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Spawning East Door"))
			Doors[1] = SpawnDoor(DoorEastSpawn, 1);
		}
		if (isDoorSouth)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Spawning South Door"))
			Doors[2] = SpawnDoor(DoorSouthSpawn, 2);
		}
		if (isDoorWest)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Spawning West Door"))
			Doors[3] = SpawnDoor(DoorWestSpawn, 3);
		}
		
		/*for (int i = 0; i < DoorArrSize; i++)
		{
			ADoor* door = Doors[i];
			
			if (door)
			{
				Doors[i] = SpawnDoor(SpawnPoints[i], i);
			}
		}*/
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Door Prebuild Set"));
	}
}

void ARoom::SetDoorsActive(bool doorsActive)
{
	if (isDoorNorth)
		Doors[0]->SetActive(doorsActive);

	if (isDoorEast)
		Doors[1]->SetActive(doorsActive);

	if (isDoorSouth)
		Doors[2]->SetActive(doorsActive);

	if (isDoorWest)
		Doors[3]->SetActive(doorsActive);
}


void ARoom::Activate()
{
	if (!bIsComplete)
	{
		SetDoorsActive(false);

		bIsActive = true;

		SpawnInterval = TimeToSpawn / RemainingEnemies;
	}
}

void ARoom::Complete()
{
	SetDoorsActive(true);
	bIsComplete = true;
	bIsActive = false;
}


