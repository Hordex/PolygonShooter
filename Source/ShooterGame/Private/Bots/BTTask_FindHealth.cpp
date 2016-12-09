// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "Bots/BTTask_FindHealth.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Bots/ShooterAIController.h"
#include "Bots/ShooterBot.h"
#include "Pickups/ShooterPickup_Health.h"
#include "Weapons/ShooterWeapon_Instant.h"

UBTTask_FindHealth::UBTTask_FindHealth(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

EBTNodeResult::Type UBTTask_FindHealth::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* MyController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	AShooterBot* MyBot = MyController ? Cast<AShooterBot>(MyController->GetPawn()) : NULL;
	if (MyBot == NULL)
	{
		return EBTNodeResult::Failed;
	}

	AShooterGameMode* GameMode = MyBot->GetWorld()->GetAuthGameMode<AShooterGameMode>();
	if (GameMode == NULL)
	{
		return EBTNodeResult::Failed;
	}

	const FVector MyLoc = MyBot->GetActorLocation();
	AShooterPickup_Health* BestPickup = NULL;
	float BestDistSq = MAX_FLT;

	for (int32 i = 0; i < GameMode->LevelPickups.Num(); ++i)
	{
		AShooterPickup_Health* HealthPickup = Cast<AShooterPickup_Health>(GameMode->LevelPickups[i]);
		if (HealthPickup && HealthPickup->CanBePickedUp(MyBot))
		{
			const float DistSq = (HealthPickup->GetActorLocation() - MyLoc).SizeSquared();
			if (BestDistSq == -1 || DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestPickup = HealthPickup;
			}
		}
	}

	if (BestPickup)
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), BestPickup->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
