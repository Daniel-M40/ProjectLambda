// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlendTriggerVolume.generated.h"

//Source - https://docs.unrealengine.com/5.2/en-US/using-a-static-camera-in-unreal-engine/
UCLASS()
class PROJECTLAMBDA_API ABlendTriggerVolume : public AActor
{
	GENERATED_BODY()

protected:
	//Collision Bounds of the Actor Volume
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* OverlapVolume;
	
	UPROPERTY(EditAnywhere, Category="Static Camera", meta=(DisplayName="Static Camera"))
	AActor* Camera;
	
	//Blend time for camera transition
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(ClampMin = 0.0f ))
	float InterpSpeed;

	//Begin and End Overlap methods for our OverlapVolume Actor
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

	
private:
	UPROPERTY(EditAnywhere, Category="Camera Config", meta=(DisplayName="Camera Location"))
	FVector CameraLocation;

	UPROPERTY(EditAnywhere, Category="Camera Config", meta=(DisplayName="Camera Rotation"))
	FRotator CameraRotation;

	bool bCameraAtLocation = true;
	
public:
	// Sets default values for this actor's properties
	ABlendTriggerVolume();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
