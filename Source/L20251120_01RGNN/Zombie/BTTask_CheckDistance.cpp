// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckDistance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "ZombieCharacter.h"

UBTTask_CheckDistance::UBTTask_CheckDistance()
{
	NodeName = TEXT("CheckBattle");
}

EBTNodeResult::Type UBTTask_CheckDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	AZombieCharacter* Zombie = Cast<AZombieCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	//UE_LOG(LogTemp, Warning, TEXT("%s %s"), *Player->GetName(), *Zombie->GetName());

	if (Player && Zombie)
	{
		FVector ZombieLocation = Zombie->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();
		float Distance = FVector::Distance(ZombieLocation, PlayerLocation);
		//UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
		switch (TargetCondition)
		{
		case ECondition::GreaterThan:
			if (Distance > TargetDistance)
			{
				Zombie->SetState(TargetState);
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), (uint8)(TargetState));
			}
			return EBTNodeResult::Succeeded;
		case ECondition::LessThan:
			if (Distance < TargetDistance)
			{
				Zombie->SetState(TargetState);
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), (uint8)(TargetState));
			}
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
