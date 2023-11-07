// Fill out your copyright notice in the Description page of Project Settings.


#include "BlendTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "ProjectLambda/Player/PlayerCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ABlendTriggerVolume::ABlendTriggerVolume()
{	
	//Create box component default components
	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraProximityVolume"));

	//Set the box component attachment to the root component.
	OverlapVolume->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned

void ABlendTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}

void ABlendTriggerVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	const APlayerCharacter* PlayerCharacterCheck = Cast<APlayerCharacter>(OtherActor);
	
	if (PlayerCharacterCheck)
	{
		APlayerController* PlayerCharacterController = Cast<APlayerController>(PlayerCharacterCheck->GetController());

		if (PlayerCharacterController && Camera)
		{
			//Cast check to see if overlapped Actor is Third Person Player Character
			//Set the actor location and rotation

			bCameraAtLocation = false;

			Camera->SetActorLocation(CameraLocation);
			Camera->SetActorRotation(CameraRotation);

			//Sets Player Controller view to the first CameraActor found
			PlayerCharacterController->SetViewTargetWithBlend(Camera, 0.f, EViewTargetBlendFunction::VTBlend_Linear);
		}

	}
	
	
}



// Called every frame
void ABlendTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get camera current location
	FVector CameraCurrentLocation = Camera->GetActorLocation();

	//If camera is not at new location then we need to move the camera there
	if (!bCameraAtLocation)
	{
		//Basically calculates some stuff to make the camera move there more "smoothly"
		const FVector NewCameraLocation = FMath::VInterpTo(CameraCurrentLocation, CameraLocation,
												  GetWorld()->GetDeltaSeconds(), InterpSpeed);

		//Set location with calculation
		Camera->SetActorLocation(NewCameraLocation);
			
		//If camera is at new location set flag to true
		bCameraAtLocation = CameraCurrentLocation.Equals(CameraLocation);
		
	}
	
}


