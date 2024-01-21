// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickUp.h"

#include "ProjectLambda/Player/PlayerCharacter.h"


// Sets default values
AAmmoPickUp::AAmmoPickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAmmoPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmoPickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//If the other actor that has collided with the pick up is the player then apply heath
	bIsPlayer = (OtherActor && OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()));
	
	UE_LOG(LogTemp, Warning, TEXT("Ammo Pickup"));

	//Increase Ammo of Players Shotgun
	if (PlayerCharacter && bIsPlayer)
	{
		PlayerCharacter->IncreaseAmmo(AmmoIncrease);

		//Handle the destruction of the object
		HandleDestruction();
	}
	
}

