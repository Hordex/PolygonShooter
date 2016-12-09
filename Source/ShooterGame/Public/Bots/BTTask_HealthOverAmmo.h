// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_HealthOverAmmo.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UBTTask_HealthOverAmmo : public UBTTaskNode
{
	GENERATED_BODY()
	

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
