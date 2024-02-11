// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomManager.h"
#include "Room.h"








// Sets default values for this component's properties
ARoomManager::ARoomManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;


}


// Called when the game starts
void ARoomManager::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Map Generating..."));

	// Initialise map of room references
	roomMap.SetNum(mapHeight);
	for (int i = 0; i < mapHeight; i++)
	{
		roomMap[i].column.SetNum(mapWidth);
		for (int j = 0; j < mapWidth; j++)
		{
			roomMap[i].column[j] = nullptr;
		}
	}

	// Try generating maps until a valid one is created
	bool mapGenerated = GenerateMap();


	while (!mapGenerated)
	{
		mapGenerated = GenerateMap();
	}


	GenerateRooms();


}


// Called every frame
void ARoomManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


ARoom* ARoomManager::GetRoomAt(int Horizontal, int Vertical)
{
	return roomMap[Horizontal].column[Vertical];
}

bool ARoomManager::GenerateMap()
{
	
	// Select a random tile to start at

	//start = { 0, 0 };



	// Make sure the path doesn't get stuck in a loop
	bool mapInvalid = false;

	start = FIntVector2D{ FMath::RandRange(0, mapHeight - 1), FMath::RandRange(0, mapWidth - 1) };

	// Initialise map to all 0s
	// (No rooms anywhere)
	if (RoomTypes.Num() > 0)
	{
		map.SetNum(mapHeight);
		for (int i = 0; i < mapHeight; i++)
		{
			map[i].column.SetNum(mapWidth);
			for (int j = 0; j < mapWidth; j++)
			{
				map[i].column[j] = { 0 };
			}
		}
	}

	else
	{
		// No room types mapped
		UE_LOG(LogTemp, Error, TEXT("No room types mapped in room manger"));
		return false;
	}


	map[start.Y].column[start.X].roomType = StartRoomCode;

	// Rooms on the main path
	// Used to generate offshoots
	TArray<FIntVector2D> aRoomsToBoss;
	FIntVector2D bossRoomPos;


	int entranceDirection = -1;
	FIntVector2D currentPos = start;

	// Make x rooms, ending in a boss room
	for (int i = 0; i <= roomsToBoss && !mapInvalid; i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Starting Main Path"));


		bool roomValid = false;
		int iterations = 0;



		// Choose random direction for next room
		int nextDirection = -1;


		// Choose a random direction
		// Different from entrance to this room
		do
		{
			nextDirection = FMath::RandRange(0, 3);

		} while (nextDirection == entranceDirection);

		// Search directions until all checked/valid found
		while (!mapInvalid && !roomValid && iterations < 4)
		{

			// Add next room
			//UE_LOG(LogTemp, Warning, TEXT("Creating Room"));
			// North, East, South, West
			
			FIntVector2D pseudoPos = currentPos;

			// Check direction for spawn
			switch ((nextDirection + iterations) % 4)
			{

				// North
			case 0:
				UE_LOG(LogTemp, Warning, TEXT("North"))
				pseudoPos.Y += 1;
				break;

				// East
			case 1:
				UE_LOG(LogTemp, Warning, TEXT("East"))
				pseudoPos.X += 1;
				break;

				// South
			case 2:
				UE_LOG(LogTemp, Warning, TEXT("South"))
				pseudoPos.Y -= 1;
				break;

				// West
			case 3:
				UE_LOG(LogTemp, Warning, TEXT("West"))
				pseudoPos.X -= 1;
				break;

			default:
				//UE_LOG(LogTemp, Error, TEXT("Something went wrong checking if the next room is valid"));
				break;
			}

			// New position is within map bounds
			if (pseudoPos.Y >= 0 && pseudoPos.Y < mapHeight && pseudoPos.X >= 0 && pseudoPos.X < mapWidth)
			{
				// No room exists in that position already
				if (map[pseudoPos.Y].column[pseudoPos.X].roomType == 0)
				{
					// Door to exit
					map[currentPos.Y].column[currentPos.X].Doors.Add((nextDirection + iterations) % 4);
					
					// Door to enter this room (from previous frame)
					map[currentPos.Y].column[currentPos.X].Doors.Add(entranceDirection);
					entranceDirection = ((nextDirection + iterations) + 2) % 4;



					// Set room
					currentPos = pseudoPos;

					roomValid = true;


					// End of path reached, create boss room
					if (i >= roomsToBoss)
					{
						map[currentPos.Y].column[currentPos.X].roomType = BossRoomCode;
						// Create door
						map[currentPos.Y].column[currentPos.X].Doors.Add(entranceDirection);
						bossRoomPos = currentPos;
					}
					// Create normal room
					else
					{
						map[currentPos.Y].column[currentPos.X].roomType = FMath::RandRange(1, RoomTypes.Num() - 1);
						aRoomsToBoss.Add(currentPos);
					}

				}
			}

			// Room could not be generated this iteration
			if (!roomValid)
			{
				// Should try again in other directions
				iterations++;

				// All directions attempted
				// Restart from the beginning
				if (iterations >= 4)
				{
					mapInvalid = true;
				}
			}

		}
	}


#pragma region

	// Generate each branching path
	for (int branchGenerated = 0; branchGenerated < numberOfBranches; branchGenerated++)
	{


		bool roomValid = false;
		int iterations = 0;



		// Choose random direction for next room
		int nextDirection;

		// Choose a random direction
		// Different from entrance to this room
		do
		{
			nextDirection = FMath::RandRange(0, 3);

		} while (nextDirection == entranceDirection);

		// Search directions until all checked/valid found
		while (!mapInvalid && !roomValid && iterations < 4)
		{

			// Add next room
			UE_LOG(LogTemp, Warning, TEXT("Creating Room"));
			// North, East, South, West

			FIntVector2D randomPos = aRoomsToBoss[FMath::RandRange(1, aRoomsToBoss.Num()-2)];

			FIntVector2D pseudoPos = randomPos;


			// Check direction for spawn
			switch ((nextDirection + iterations) % 4)
			{

				// North
			case 0:
				pseudoPos.Y += 1;
				break;

				// East
			case 1:
				pseudoPos.X += 1;
				break;

				// South
			case 2:
				pseudoPos.Y -= 1;
				break;

				// West
			case 3:
				pseudoPos.X -= 1;
				break;

			default:
				UE_LOG(LogTemp, Error, TEXT("Something went wrong checking if the next room is valid"));
				break;
			}

			// New position is within map bounds
			if (pseudoPos.Y >= 0 && pseudoPos.Y < mapHeight && pseudoPos.X >= 0 && pseudoPos.X < mapWidth)
			{
				// No room exists in that position already
				if (map[pseudoPos.Y].column[pseudoPos.X].roomType == 0)
				{
					// Add door flags
					map[pseudoPos.Y].column[pseudoPos.X].Doors.Add((nextDirection + iterations + 2) % 4);
					map[randomPos.Y].column[randomPos.X].Doors.Add((nextDirection + iterations) % 4);

					// Set room
					currentPos = pseudoPos;
					UE_LOG(LogTemp, Warning, TEXT("Adding branch"));
					roomValid = true;

					//aRoomsToBoss.Add(randomPos);

					// Create normal room
					map[pseudoPos.Y].column[pseudoPos.X].roomType = FMath::RandRange(1, RoomTypes.Num() - 1);



				}
			}

			// Room could not be generated this iteration
			if (!roomValid)
			{
				// Should try again in other directions
				iterations++;

				// All directions attempted
				// Restart from the beginning
				if (iterations >= 4)
				{
					mapInvalid = true;
				}
			}

		}
	}

#pragma endregion



	UE_LOG(LogTemp, Warning, TEXT("Loop Complete"));

	// True if was generated
	// False if was not generated
	return !mapInvalid;
}

void ARoomManager::SpawnRoom(ARoom* Room, int horizontal, int vertical)
{
	if (Room)
	{
		Room->Setup(this, horizontal, vertical);
		roomMap[horizontal].column[vertical] = Room;

		for (int door : map[horizontal].column[vertical].Doors)
		{
			roomMap[horizontal].column[vertical]->SetDoor(door);
		}

		roomMap[horizontal].column[vertical]->SpawnDoors();
	}
}

void ARoomManager::SpawnStartRoom(ARoom* Room, int horizontal, int vertical)
{
	if (Room)
	{
		Room->Setup(this, horizontal, vertical);
		roomMap[horizontal].column[vertical] = Room;

		for (int door : map[horizontal].column[vertical].Doors)
		{
			roomMap[horizontal].column[vertical]->SetDoor(door);
		}

		roomMap[horizontal].column[vertical]->SpawnDoors();

		// Move player to start Room

		// -- TEMPORARY FOR TESTING --
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(Room->GetActorLocation() + (FVector::UpVector *  SpawnHeight));

		roomMap[horizontal].column[vertical]->Activate();
	}
}


bool ARoomManager::GenerateRooms()
{
	for (int horizontal = 0; horizontal < mapHeight; horizontal++)
	{
		for (int vertical = 0; vertical < mapWidth; vertical++)
		{
			// 0 Means no room
			if (map[horizontal].column[vertical].roomType > 0)
			{
				ARoom* Room = GetWorld()->SpawnActor<ARoom>(RoomTypes[map[horizontal].column[vertical].roomType], FVector(vertical * roomInterval, horizontal * roomInterval, GetActorLocation().Z), GetActorRotation());

				SpawnRoom(Room, horizontal, vertical);


			}
			// -1 is boss room
			else if (map[horizontal].column[vertical].roomType == BossRoomCode)
			{
				ARoom* Room = GetWorld()->SpawnActor<ARoom>(BossRoomClass, FVector(vertical * roomInterval, horizontal * roomInterval, GetActorLocation().Z), GetActorRotation());
				
				SpawnRoom(Room, horizontal, vertical);



			}
			// -2 is start room
			else if (map[horizontal].column[vertical].roomType == StartRoomCode)
			{
				ARoom* Room = GetWorld()->SpawnActor<ARoom>(StartRoomClass, FVector(vertical * roomInterval, horizontal * roomInterval, GetActorLocation().Z), GetActorRotation());

				SpawnStartRoom(Room, horizontal, vertical);

			}
		}
	}

	return true;
}






