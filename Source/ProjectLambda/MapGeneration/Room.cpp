// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "Door.h"
#include "RoomManager.h"

<<<<<<< HEAD
#include "../AI/BaseEnemyCharacter.h"

#include "NavigationSystem.h"

#include "Kismet/GameplayStatics.h"
#include "../ProjectLambdaGameModeBase.h"

=======
>>>>>>> parent of 8e1b0ee (Doors Working, Enemy Spawning Started)
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

<<<<<<< HEAD
	//GetActorBounds(false, RoomOrigin, RoomBounds);
	RoomOrigin = GetActorLocation();
	GameMode = Cast<AProjectLambdaGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		Manager = GameMode->GetMapManager();

		if (Manager)
		{
			Setup(Manager);
		}

		GameMode->RegisterRoom(this, GridHorizontal, GridVertical);
	}
=======




>>>>>>> parent of 8e1b0ee (Doors Working, Enemy Spawning Started)
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

<<<<<<< HEAD
	if (bIsActive)
	{
		if (RemainingEnemies > 0)
		{
			SpawnTimer += DeltaTime;

			if (SpawnTimer >= SpawnInterval)
			{
				SpawnTimer -= SpawnInterval;

				// Spawn the enemy
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
	// Get the player position

	FVector Pos = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	
	// Set the Y to something reasonible 
	Pos.Y = 10.f;


	FVector MinNoSpawn =  Pos -	FVector(CameraSizeX / 2.f - SpawnPositionBuffer, CameraSizeY / 2.f, 0.f - SpawnPositionBuffer);
	FVector MaxNoSpawn =  Pos + FVector(CameraSizeX / 2.f + SpawnPositionBuffer, CameraSizeY / 2.f, 0.f + SpawnPositionBuffer);

	FVector RoomMin = RoomOrigin - RoomBounds;
	FVector RoomMax = RoomOrigin + RoomBounds;

	FVector Spawn;
	

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	FVector Hit;
	FVector RayStart;
	FVector RayEnd;

	do
	{
		if (RoomMin.X < MinNoSpawn.X && RoomMax.X > MaxNoSpawn.X)
		{
			// Spawn Random
			if (FMath::RandBool())
			{
				Spawn.X = FMath::RandRange(RoomMin.X, MinNoSpawn.X);
			}
			else
			{
				Spawn.X = FMath::RandRange(RoomMax.X, MaxNoSpawn.X);
			}
		}
		else if (RoomMin.X < MinNoSpawn.X)
		{
			// Spawn Negative X
			Spawn.X = FMath::RandRange(RoomMin.X, MinNoSpawn.X);
		}
		else if (RoomMax.X > MaxNoSpawn.X)
		{
			// Spawn Positive X
			Spawn.X = FMath::RandRange(RoomMax.X, MaxNoSpawn.X);
		}
		else
		{
			// Enemy Cannot Spawn
			UE_LOG(LogTemp, Warning, TEXT("Enemy Cannot Spawn X"));
		}




		if (RoomMin.Y < MinNoSpawn.Y && RoomMax.Y > MaxNoSpawn.Y)
		{
			// Spawn Random
			if (FMath::RandBool())
			{
				Spawn.Y = FMath::RandRange(RoomMin.Y, MinNoSpawn.Y);
			}
			else
			{
				Spawn.Y = FMath::RandRange(RoomMax.Y, MaxNoSpawn.Y);
			}
		}
		else if (RoomMin.Y < MinNoSpawn.Y)
		{
			// Spawn Negative X
			Spawn.Y = FMath::RandRange(RoomMin.Y, MinNoSpawn.Y);
		}
		else if (RoomMax.Y > MaxNoSpawn.Y)
		{
			// Spawn Positive X
			Spawn.Y = FMath::RandRange(RoomMax.Y, MaxNoSpawn.Y);
		}
		else
		{
			// Enemy Cannot Spawn
			UE_LOG(LogTemp, Warning, TEXT("Enemy Cannot Spawn Y"));
		}

		// I hate this but idk another way of doing it
		RayStart = Spawn;
		RayEnd = Spawn;
		RayStart.Z = 20.f;
		RayEnd.Z = 20.f;


		NavSystem->NavigationRaycast(nullptr, RayStart, RayEnd, Hit);

	} while (Hit != RayEnd);
	
	Hit.Z = 25.f;

	return Hit;
}

void ARoom::CalculateCameraSize()
{
	float FOV = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetFOVAngle();
	float Opposite = FMath::Atan(FOV) * GetActorLocation().Z;

	CameraSizeX = Opposite;
	
	// Can't think of a good way to get Y, enemies will just spawn further away on this axis
	CameraSizeY = Opposite;
}

=======
}


>>>>>>> parent of 8e1b0ee (Doors Working, Enemy Spawning Started)
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


void ARoom::Setup(ARoomManager* _Manager)
{
	Manager = _Manager;

	
	FVector pos = GetActorLocation();
	Manager->CalculateMapCoords(pos.X, pos.Y, GridHorizontal, GridVertical);
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
<<<<<<< HEAD
}

void ARoom::SetDoorsActive(bool doorsActive)
{
	if (isDoorNorth)
		DoorNorth->SetActive(doorsActive);

	if (isDoorEast)
		DoorEast->SetActive(doorsActive);

	if (isDoorSouth)
		DoorSouth->SetActive(doorsActive);

	if (isDoorWest)
		DoorWest->SetActive(doorsActive);
}

AProjectLambdaGameModeBase* ARoom::GetGameMode()
{
	return GameMode;
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
	bIsComplete = true;
	bIsActive = false;
	SetDoorsActive(true);
=======
>>>>>>> parent of 8e1b0ee (Doors Working, Enemy Spawning Started)
}