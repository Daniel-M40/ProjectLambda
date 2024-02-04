// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotgunAmmoPickUp.h"

#include "ProjectLambda/Player/PlayerCharacter.h"


// Sets default values
AShotgunAmmoPickUp::AShotgunAmmoPickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShotgunAmmoPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShotgunAmmoPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShotgunAmmoPickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//If the other actor that has collided with the pick up is the player then apply heath
	bIsPlayer = (OtherActor && OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()));
	
	UE_LOG(LogTemp, Warning, TEXT("Ammo Pickup"));

	//Increase Ammo of Players currently held weapon 
	if (PlayerCharacter && bIsPlayer)
	{
		PlayerCharacter->IncreaseShotgunAmmo(AmmoIncrease);

		//Handle the destruction of the object
		HandleDestruction();
	}
	
}

