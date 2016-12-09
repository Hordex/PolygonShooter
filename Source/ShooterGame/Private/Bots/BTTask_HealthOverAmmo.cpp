// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "BTTask_HealthOverAmmo.h"
#include "Bots/ShooterAIController.h"
#include "Bots/ShooterBot.h"
#include "Weapons/ShooterWeapon.h"


EBTNodeResult::Type UBTTask_HealthOverAmmo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AShooterAIController* MyController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	AShooterBot* MyBot = MyController ? Cast<AShooterBot>(MyController->GetPawn()) : NULL;
	
	if (MyBot == NULL)
	{
		return EBTNodeResult::Failed;
	}
	AShooterWeapon* MyWeapon = MyBot->GetWeapon();
	if (!MyWeapon)
	{
		return EBTNodeResult::Succeeded;
	}
	AShooterGameMode* GameMode = MyBot->GetWorld()->GetAuthGameMode<AShooterGameMode>();
	if (GameMode == NULL)
	{
		return EBTNodeResult::Failed;
	}

	if(MyBot->Health < MyBot->GetMaxHealth()* MyBot->GetLowHealthPercentage() || MyBot->Health / MyBot->GetMaxHealth() < MyWeapon->GetCurrentAmmo() / MyWeapon->GetMaxAmmo())
	{ 
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
