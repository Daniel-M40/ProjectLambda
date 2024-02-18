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
	
	
	UE_LOG(LogTemp, Warning, TEXT("Set Stats InitSpeed: %f"), ProjectileMovement->InitialSpeed);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// I do not know why it requires it here.
	// Blueprint setting didn't work.
	SetLifeSpan(0.4f);

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

	// If enemy spawn enemy hit particle (blood)
	if (OtherActor->ActorHasTag("Enemy"))
	{
		UNiagaraComponent* particles = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), EnemyHitParticles, GetActorLocation(), GetVelocity().Rotation().GetInverse());

		if (particles != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning blood particle at %s"), *this->GetName());
		}
	}
	// Anything else, spawn spark
	else
	{

		
		UNiagaraComponent* particles = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), GenericHitParticles, GetActorLocation(), HitResult.ImpactNormal.Rotation());

		if (particles != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning generic particle at %s"), *this->GetName());
		}
	}

	//Destroy the actor if we have collided with anything
	Destroy();
}

