// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "Door.h"
#include "RoomManager.h"

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





}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool ARoom::SetDoor(int direction, bool isDoor)
{
	bool doorGenerated = false;

	switch (direction)
	{
	case 0:
		isDoorNorth = true;
		doorGenerated = true;
		break;
	case 1:
		isDoorEast = true;
		doorGenerated = true;
		break;
	case 2:
		isDoorSouth = true;
		doorGenerated = true;
		break;
	case 3:
		isDoorWest = true;
		doorGenerated = true;
		break;
	}

	return doorGenerated;
}

ADoor* ARoom::GetDoor(int direction)
{
	ADoor* door = nullptr;
	switch (direction)
	{
		case 0:
			door = DoorNorth;
			break;

		case 1:
			door = DoorEast;
			break;

		case 2:
			door = DoorSouth;
			break;

		case 3:
			door = DoorWest;
			break;
	}
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

void ARoom::SpawnDoors()
{
	if (DoorPrebuild)
	{
		if (isDoorNorth)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Spawning North Door"))
			DoorNorth = GetWorld()->SpawnActor<ADoor>(DoorPrebuild, DoorNorthSpawn->GetComponentLocation(), DoorNorthSpawn->GetComponentRotation());
			DoorNorth->AttachToComponent(DoorNorthSpawn, FAttachmentTransformRules::KeepWorldTransform);

		}
		if (isDoorEast)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Spawning East Door"))
			DoorEast = GetWorld()->SpawnActor<ADoor>(DoorPrebuild, DoorEastSpawn->GetComponentLocation(), DoorEastSpawn->GetComponentRotation());
			DoorEast->AttachToComponent(DoorEastSpawn, FAttachmentTransformRules::KeepWorldTransform);
		}
		if (isDoorSouth)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Spawning South Door"))
			DoorSouth = GetWorld()->SpawnActor<ADoor>(DoorPrebuild, DoorSouthSpawn->GetComponentLocation(), DoorSouthSpawn->GetComponentRotation());
			DoorSouth->AttachToComponent(DoorSouthSpawn, FAttachmentTransformRules::KeepWorldTransform);
		}
		if (isDoorWest)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Spawning West Door"))
			DoorWest = GetWorld()->SpawnActor<ADoor>(DoorPrebuild, DoorWestSpawn->GetComponentLocation(), DoorWestSpawn->GetComponentRotation());
			DoorWest->AttachToComponent(DoorWestSpawn, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Door Prebuild Set"));
	}
}