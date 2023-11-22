// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Player Location";
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the player controller
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		//Get the location of the player
		FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);

		//Finish with success
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
