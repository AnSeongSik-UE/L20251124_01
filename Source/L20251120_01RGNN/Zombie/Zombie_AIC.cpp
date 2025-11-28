// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie_AIC.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "../MyTPC.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ZombieCharacter.h"

AZombie_AIC::AZombie_AIC()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	UAISenseConfig_Sight* Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = 500.0f;				//인식거리
	Sight->LoseSightRadius = 600.0f;			//놓침거리
	Sight->PeripheralVisionAngleDegrees = 45.0f;//시야각
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->SetMaxAge(3);						//망각시간 0이면 영원히 안까먹음
	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());

}

void AZombie_AIC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//ensure(RunBTAsset);
	if (RunBTAsset)
	{
		RunBehaviorTree(RunBTAsset);
	}
	//Perception->OnPerceptionUpdated.AddDynamic(this, &AZombie_AIC::ProcessPerception);
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AZombie_AIC::ProcessActorPerception);
	Perception->OnTargetPerceptionForgotten.AddDynamic(this, &AZombie_AIC::ProcessActorPerceptionForget);
	//Perception->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AZombie_AIC::ProcessActorPerceptionInfo);
	SetGenericTeamId(3); // 255는 중립
}

void AZombie_AIC::OnUnPossess()
{
	Super::OnUnPossess();
}

void AZombie_AIC::ProcessPerception(const TArray<AActor*>& UpdatedActors)
{
	for (auto Actor : UpdatedActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("ProcessPerception %s"), *Actor->GetName());
	}
}

void AZombie_AIC::ProcessActorPerception(AActor* Actor, FAIStimulus Stimulus)
{
	//UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerception %s %s"), *Actor->GetName(), *Stimulus.Type.Name.ToString());
	
	//시야
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		AMyTPC* Player = Cast<AMyTPC>(Actor);
		AZombieCharacter* Zombie = Cast<AZombieCharacter>(GetPawn());
		if (Player && Zombie)
		{
			if (Stimulus.WasSuccessfullySensed()) //시야에 들어옴
			{
				if (Zombie->GetCurrentState() == EZombieState::Death)
				{
					return;
				}
				Blackboard->SetValueAsObject(TEXT("Target"), Player);
				SetState(EZombieState::Chase);
				Zombie->SetState(EZombieState::Chase);
				Zombie->ChangeSpeed(500.0f);
			}
			else // 시야에서 놓침
			{
				if (Zombie->GetCurrentState() == EZombieState::Death)
				{
					return;
				}
				Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
				SetState(EZombieState::Normal);
				Zombie->SetState(EZombieState::Normal);
				Zombie->ChangeSpeed(80.0f);
			}
		}
	}
}

void AZombie_AIC::ProcessActorPerceptionForget(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerceptionForget %s"), *Actor->GetName());
	
	AMyTPC* Player = Cast<AMyTPC>(Actor);
	AZombieCharacter* Zombie = Cast<AZombieCharacter>(GetPawn());
	if (Player && Zombie)
	{
		if (Zombie->GetCurrentState() == EZombieState::Death)
		{
			return;
		}
		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
		SetState(EZombieState::Normal);
		Zombie->SetState(EZombieState::Normal);
		Zombie->ChangeSpeed(80.0f);
	}
}

void AZombie_AIC::ProcessActorPerceptionInfo(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerceptionInfo %s"), *UpdateInfo.Target->GetName());
}

void AZombie_AIC::SetState(EZombieState NewState)
{
	Blackboard->SetValueAsEnum(TEXT("CurrentState"), (uint8)(NewState));
}