// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class ARoom;

UCLASS()
class PROJECTLAMBDA_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Setup(ARoom* _Room, int Direction);

	UFUNCTION()
		void Enter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		USceneComponent* GetExitPosition();

<<<<<<< HEAD
	UFUNCTION()
		void SetActive(bool Active);

	UFUNCTION()
		ARoom* GetRoom();
=======
>>>>>>> parent of 8e1b0ee (Doors Working, Enemy Spawning Started)
private:
	
	int FacingDirection;
	ARoom* Room;

	bool DoorEnabled = false;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* Trigger;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* ExitPosition;
};
