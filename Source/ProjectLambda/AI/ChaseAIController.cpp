// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseAIController.h"
#include "BaseEnemyCharacter.h"

AChaseAIController::AChaseAIController(FObjectInitializer const& ObjectInitializer)
{
}

void AChaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ABaseEnemyCharacter* const enemy = Cast<ABaseEnemyCharacter>(InPawn))
	{
		if (UBehaviorTree* const tree = enemy->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b); //Ensure the blackboard exists
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
