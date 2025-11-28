// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie_AIC.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AZombie_AIC::AZombie_AIC()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	UAISenseConfig_Sight* Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = 300.0f;				//인식거리
	Sight->LoseSightRadius = 400.0f;			//놓침거리
	Sight->PeripheralVisionAngleDegrees = 45.0f;//시야각
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->SetMaxAge(0);						//망각시간 0이면 바로 까먹음
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
	Perception->OnPerceptionUpdated.AddDynamic(this, &AZombie_AIC::ProcessPerception);
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AZombie_AIC::ProcessActorPerception);
	Perception->OnTargetPerceptionForgotten.AddDynamic(this, &AZombie_AIC::ProcessActorPerceptionForget);
	Perception->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AZombie_AIC::ProcessActorPerceptionInfo);
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
	UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerception %s %s"), *Actor->GetName(), *Stimulus.Type.Name.ToString());
}

void AZombie_AIC::ProcessActorPerceptionForget(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerceptionForget %s"), *Actor->GetName());
}

void AZombie_AIC::ProcessActorPerceptionInfo(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerceptionInfo %s"), *UpdateInfo.Target->GetName());
}
