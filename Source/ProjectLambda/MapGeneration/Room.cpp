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
	SpawnPoints.Add(DoorSouthSpawn);
	SpawnPoints.Add(DoorWestSpawn);
	
	//GetActorBounds(false, RoomOrigin, RoomBounds);
	
	//GetActorBounds(false, RoomOrigin, RoomBounds);
	RoomOrigin = GetActorLocation();

	RemainingEnemies = EnemyWave.Num() - 1;
	EnemiesToKill = EnemyWave.Num() - 1;
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
				ABaseEnemyCharacter* enemy = GetWorld()->SpawnActor<ABaseEnemyCharacter>(EnemyWave[EnemyWave.Num() - 1 - RemainingEnemies], GenerateEnemySpawnPos(), FRotator::ZeroRotator);

				enemy->SetOwner(this);

				RemainingEnemies--;
			}
		}


		if (EnemiesToKill <= 0)
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
		ADoor* Door = Doors[SpawnDoor];

		//If the door is in use spawn enemies at door location
		if (Door && Door->bIsInUse)
		{
			SpawnPos = Door->GetExitPosition()->GetComponentLocation();
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
	if (direction >= 0)
	{
		Doors[direction]->bIsInUse = true;
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
		for (int i = 0; i < DoorArrSize; i++)
		{
			ADoor* door = Doors[i];

			//If the door is used in room, spawn door at location and rotation
			if (door && door->bIsInUse)
			{
				ADoor* tempDoor = SpawnDoor(SpawnPoints[i], i);
				
				//As we have assigned the temp door a flag to say whether
				//it is active or in use we need to assign that value to the door we have spawned
				tempDoor->bIsInUse = Doors[i]->bIsInUse;
				tempDoor->bIsActive = Doors[i]->bIsActive;
				
				Doors[i] = tempDoor;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Door Class Set"));
	}
}

void ARoom::SetDoorsActive(bool bIsDoorActive)
{
	for (ADoor* Door : Doors)
	{
		if (Door && Door->bIsInUse)
		{
			Door->SetActive(bIsDoorActive);
		}
	}
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
	UE_LOG(LogTemp, Warning, TEXT("Room Complete"))
	SetDoorsActive(true);
	bIsComplete = true;
	bIsActive = false;
}


void ARoom::EnemyDied()
{
	EnemiesToKill--;
}