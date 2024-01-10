// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickUp.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectLambda/GameModes/CoreGameMode.h"
#include "ProjectLambda/Player/PlayerCharacter.h"


// Sets default values
ABasePickUp::ABasePickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	RootComponent = BaseMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComponent->SetupAttachment(BaseMesh);
	SphereComponent->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void ABasePickUp::BeginPlay()
{
	Super::BeginPlay();

	//Add dynamic delegate for sphere collision overlap
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasePickUp::OnBeginOverlap);

	//Get game mode ref
	CoreGameMode = Cast<ACoreGameMode>(UGameplayStatics::GetGameMode(this));

	//Get player character
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	//Timer to despawn pick after certain amount of time
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ABasePickUp::DestroyPickUp, SpawnTime,
		false);
}

// Called every frame
void ABasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
}

void ABasePickUp::HandleDestruction()
{
	//@@TODO Spawn visual effects and sound effects here
	if (bIsPlayer)
	{
		
		Destroy();
	}
}

void ABasePickUp::DestroyPickUp()
{
	Destroy();
}

