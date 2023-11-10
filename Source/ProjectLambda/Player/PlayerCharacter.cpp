// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Static mesh for the player
	playerStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	playerStaticMesh->SetupAttachment(RootComponent);
	
	
	//Auto posses player when the game starts
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Get the player controller
	PlayerController = Cast<APlayerController>(GetController());
	
	if (PlayerController)
	{
		
		//Get the subsystem from the player controller
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		//Add the mapping context to the subsystem
		Subsystem->AddMappingContext(MappingContext, 0);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PlayerController)
	{		
		FHitResult HitResult;

		//Get the hit result from the cursor
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		//DEBUGGER: Draw debug sphere at cursor location
		if (bIsDebug)
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, SphereRadius, SphereSegments, FColor::Red);
		}

		//Rotate the player to where the cursor it located
		RotatePlayer(HitResult.ImpactPoint, mRotationSpeed);

	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EIC == nullptr)
		return;
	
	EIC->BindAction(MoveInput, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveHandler);
	EIC->BindAction(StrafeInput, ETriggerEvent::Triggered, this, &APlayerCharacter::StrafeHandler);
	EIC->BindAction(ShootInput, ETriggerEvent::Triggered, this, &APlayerCharacter::ShootHandler);
}


void APlayerCharacter::RotatePlayer(const FVector& LookAtTarget, const float RotateSpeed)
{
	//Get target location Mouse location - Current Location
	const FVector CurrentLocation = GetActorLocation();

	//Calculate the rotation using the location of the mouse
	const FRotator TargetRotation(0.f, UKismetMathLibrary::FindLookAtRotation(CurrentLocation, LookAtTarget).Yaw, 0.f);
		
	//Update Yaw component
	SetActorRotation(TargetRotation);
}

void APlayerCharacter::MoveHandler(const FInputActionValue& Value)
{
	AddMovementInput(FVector::ForwardVector * Value.Get<float>());
}

void APlayerCharacter::StrafeHandler(const FInputActionValue& Value)
{
	AddMovementInput(FVector::RightVector * Value.Get<float>());
}

void APlayerCharacter::ShootHandler(const FInputActionValue& Value)
{
	//@@TODO Add shooting functionality
}

void APlayerCharacter::AttachWeapon(TSubclassOf<AActor> weaponClass, FName socketName)
{
	//Get the orientation of the socket
	const FTransform orientation = GetMesh()->GetSocketTransform(socketName, ERelativeTransformSpace::RTS_World);
	
	//Spawn in the weapon
	AActor* newWeapon = GetWorld()->SpawnActor(weaponClass, &orientation);
	if (newWeapon == nullptr)
	{
		return;
	}

	//Attach the weapon to the player
	newWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);
}
