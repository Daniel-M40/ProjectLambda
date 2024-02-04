// Fill out your copyright notice in the Description page of Project Settings.



#include "CurrencyPickUp.h"
#include "ProjectLambda/Player/PlayerCharacter.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"

// Sets default values
ACurrencyPickUp::ACurrencyPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACurrencyPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACurrencyPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACurrencyPickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	//If the other actor that has collided with the pick up is the player then apply heath
	bIsPlayer = (OtherActor && OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()));

	UE_LOG(LogTemp, Warning, TEXT("Increase Money"));

	
	if (PlayerCharacter && bIsPlayer)
	{
		CoreGameMode->IncreaseCurrency(CurrencyIncrease);

		//Handle the destruction of the object
		HandleDestruction();
	}


}




