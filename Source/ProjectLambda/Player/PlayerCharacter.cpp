// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Weapons\WeaponBase.h"

#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapons/Pistol/Pistol.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Static mesh for the player
	PlayerStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	PlayerStaticMesh->SetupAttachment(RootComponent);

	
	WeaponPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Position"));
	WeaponPosition->SetupAttachment(PlayerStaticMesh);
	
	
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

	//Set gun component location and rotation
	//Pistol is default gun
	if (PistolClass)
	{
		CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(PistolClass);
		
		CurrentWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		CurrentWeapon->SetActorLocation(WeaponPosition->GetComponentLocation());
	}
}

void APlayerCharacter::ResetDash()
{
	bLaunchOnce = true;
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
		RotatePlayer(HitResult.ImpactPoint, RotationSpeed);

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
	EIC->BindAction(DashInput, ETriggerEvent::Triggered, this, &APlayerCharacter::DashHandler);
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
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
}

void APlayerCharacter::DashHandler(const FInputActionValue& Value)
{
	if (bLaunchOnce)
	{		
		//Get player velocity
		FVector ActorVelocity = GetVelocity();

		//If the player isn't moving then early return and do not launch the player
		if (ActorVelocity.IsZero())
		{
			return;
		}

		//Multiply the players velocity with the launch force
		const FVector LaunchVector = ActorVelocity * LaunchForce;

		//Call launch character function and do not override x,y,z axis
		LaunchCharacter(LaunchVector, false, false);

		//After launching the player set flag to false to prevent the user from spamming the dash
		bLaunchOnce = false;

		//Set timer for dash
		GetWorldTimerManager().SetTimer(DashTimeHandle, this,
			&APlayerCharacter::ResetDash, DashDelay, false);

		//@@TODO Add particles / sound here
	}
}



void APlayerCharacter::AttachWeapon(TSubclassOf<AWeaponBase> weaponClass, FName socketName)
{
	/*//Get the orientation of the socket
	const FTransform orientation = PlayerStaticMesh->GetSocketTransform(socketName, ERelativeTransformSpace::RTS_World);
	
	//Spawn in the weapon
	APistol* newWeapon = (APistol*) GetWorld()->SpawnActor(weaponClass, &orientation);
	if (newWeapon == nullptr)
	{
		return nullptr;
	}

	//Attach the weapon to the player
	newWeapon->AttachToComponent(PlayerStaticMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);
	return newWeapon;*/
}
