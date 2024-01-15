// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Static mesh for the projectile
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	ProjectileMesh->SetSimulatePhysics(true);

	//Projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	SetProjectileStats(ProjectileDamage, ProjecitleInitialSpeed, ProjectileMaxSpeed, Lifespan);
}

void AProjectile::SetProjectileStats(float Damage, float InitSpeed, float MaxSpeed, float LifeSpan)
{
	ProjectileDamage = Damage;
	
	ProjectileMovement->MaxSpeed = MaxSpeed;
	ProjectileMovement->InitialSpeed = InitSpeed;
	InitialLifeSpan = LifeSpan;

	ProjectileMaxSpeed = MaxSpeed;
	
	ProjectileMovement->AddForce(GetActorForwardVector() * MaxSpeed);
	
	UE_LOG(LogTemp, Warning, TEXT("Set Stats InitSpeed: %f"), ProjectileMovement->InitialSpeed);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	UE_LOG(LogTemp, Warning, TEXT("BP InitSpeed: %f"), ProjectileMovement->InitialSpeed);
	
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& HitResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit InitSpeed: %f"), ProjectileMovement->InitialSpeed);
	const AActor* CurrentOwner = GetOwner();

	//If we dont have a current owner destroy the projectile
	if (!CurrentOwner || OtherActor == nullptr)
	{
		Destroy();
		return;
	}

	//If the projectile has collided with itself ignore the collision
	if (OtherActor && OtherActor->GetClass()->IsChildOf(AProjectile::StaticClass()))
	{
		return;
	}
	
	if (CurrentOwner)
	{
		AController* CurrentInstigator = CurrentOwner->GetInstigatorController(); 
		UClass* DamageTypeClass = UDamageType::StaticClass();

		if (OtherActor && OtherActor != this && OtherActor != CurrentOwner)
		{
			UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, CurrentInstigator, this, DamageTypeClass);

			//@@TODO Add sound / particles here
		}
		
	}

	//Destroy the actor if we have collided with anything
	Destroy();
}

