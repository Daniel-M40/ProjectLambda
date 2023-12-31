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

	UFUNCTION()
		void SetActive(bool Active);

	UFUNCTION()
		ARoom* GetRoom();
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

public:
	//Flag to show whether you can move through the door or not
	UPROPERTY(VisibleAnywhere)
		bool bIsActive = false;

	//Flag to show whether the door should spawn or not
	UPROPERTY(VisibleAnywhere)
		bool bIsInUse = false;
};
