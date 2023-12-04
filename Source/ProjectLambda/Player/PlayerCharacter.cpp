// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Weapons\WeaponBase.h"

#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectLambda/Components/HealthComponent.h"
#include "Weapons/Pistol/PistolWeapon.h"
#include "Weapons/Shotgun/Shotgun.h"

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
	
	//fires event when player collides with another actor
	PlayerStaticMesh->SetNotifyRigidBodyCollision(true);

	//Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	
	//Auto posses player when the game starts
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Ammo = MaxAmmo;

	// set health to max health
	CurrentHealth = MaxHealth;
	// Calls the OnHit Funtion when a collision happens
	OnActorHit.AddDynamic(this, &APlayerCharacter::OnHit);

	//Get the player controller
	PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{

		//Get the subsystem from the player controller
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		//Add the mapping context to the subsystem
		Subsystem->AddMappingContext(MappingContext, 0);
	}

	
	//Pistol is default gun
	if (PistolClass)
	{
		//Spawn pistol
		//Set current weapon
		CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(PistolClass);

		//Add pistol to Weapon array
		Weapons.Add(CurrentWeapon);

		//Attach weapon to player
		AttachWeapon();
	}

	//Add shotgun to weapons array
	if (ShotgunClass)
	{
		AWeaponBase* tempShotgun = GetWorld()->SpawnActor<AWeaponBase>(ShotgunClass);

		//Hide actor in world
		tempShotgun->SetActorHiddenInGame(true);

		Weapons.Add(tempShotgun);
	}

	//Set weapon length
	WeaponLength = Weapons.Num();
}

void APlayerCharacter::ResetDash()
{
	bLaunchOnce = true;
}

void APlayerCharacter::SwapWeaponHandler(const FInputActionValue& Value)
{
	WeaponIndex += Value.Get<float>();
	
	//Hide old weapon
	CurrentWeapon->SetActorHiddenInGame(true);
	
	//Check if weapon is in range
	//If upper bound / lower bound wrap round
	if (WeaponIndex >= WeaponLength)
	{
		WeaponIndex = 0;
	}
	else if (WeaponIndex < 0)
	{
		WeaponIndex = WeaponLength - 1;
	}

	//Set weapon
	CurrentWeapon = Weapons[WeaponIndex];

	//Set position of weapon
	AttachWeapon();

	//Unhide new weapon
	CurrentWeapon->SetActorHiddenInGame(false);

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

	#pragma region Bind Actions
	EIC->BindAction(MoveInput, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveHandler);
	EIC->BindAction(StrafeInput, ETriggerEvent::Triggered, this, &APlayerCharacter::StrafeHandler);
	EIC->BindAction(ShootInput, ETriggerEvent::Triggered, this, &APlayerCharacter::ShootHandler);
	EIC->BindAction(DashInput, ETriggerEvent::Triggered, this, &APlayerCharacter::DashHandler);
	EIC->BindAction(SwapWeaponInput, ETriggerEvent::Triggered, this, &APlayerCharacter::SwapWeaponHandler);
	#pragma endregion
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
	//shooting functionality
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();

		if (Ammo > 0)
		{
			Ammo--; // decrease ammo when player shoots
		}
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



void APlayerCharacter::AttachWeapon()
{
	//Set gun component location and rotation
	CurrentWeapon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	CurrentWeapon->SetActorLocation(WeaponPosition->GetComponentLocation());
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{

	//If we have health component apply damage
	if (HealthComponent)
	{
		CurrentHealth = HealthComponent->ApplyDamage(DamageAmount, false); // call apply damage function to get the current value of character's health
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


void APlayerCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision Test")); //tests if collision works
}

void APlayerCharacter::HandleDestruction()
{
	//@@TODO Player sound and spawn effects here
	
	Destroy();
}
