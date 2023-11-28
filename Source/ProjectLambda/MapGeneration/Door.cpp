// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "Components/BoxComponent.h"
#include "Room.h"
#include "RoomManager.h"
#include "../Player/PlayerCharacter.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	RootComponent = DoorMesh;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Trigger"));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetGenerateOverlapEvents(true);


}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADoor::Enter);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADoor::Enter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
	{
		int GridHorizontal;
		int GridVertical;

		Room->GetCoords(GridHorizontal, GridVertical);

		switch (FacingDirection)
		{
		case 0:
			GridVertical += 1;
			break;

		case 1:
			GridHorizontal += 1;
			break;

		case 2:
			GridVertical -= 1;
			break;
		case 3:
			GridHorizontal -= 1;
			break;
		}

		ADoor* OtherDoor = Room->GetManager()->GetRoomAt(GridHorizontal, GridVertical)->GetDoor((FacingDirection + 2) % 4);

		if (OtherDoor)
		{
			USceneComponent* Exit = OtherDoor->GetExitPosition();
			OtherActor->SetActorLocationAndRotation(Exit->GetComponentLocation(), Exit->GetComponentRotation());
		}
	}
}

USceneComponent* ADoor::GetExitPosition()
{
	return ExitPosition;
}


void ADoor::Setup(ARoom* _Room, int Direction)
{
	Room = _Room;
	FacingDirection = Direction;
}