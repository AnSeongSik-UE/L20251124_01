// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LookTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ZombieCharacter.h"
#include "GameFramework/Character.h"

#include "Kismet/KismetMathLibrary.h"

UBTService_LookTarget::UBTService_LookTarget()
{
	NodeName = TEXT("LookTarget");
}

void UBTService_LookTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACharacter* Target = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Target)
	{
		AZombieCharacter* Zombie = Cast<AZombieCharacter>(OwnerComp.GetAIOwner()->GetPawn());

		FRotator LookDirection = UKismetMathLibrary::FindLookAtRotation(Zombie->GetActorLocation(), Target->GetActorLocation());

		FRotator TargetRotation = FMath::RInterpTo(Zombie->GetActorRotation(), LookDirection, DeltaSeconds, 15.0f);

		TargetRotation.Pitch = 0;

		Zombie->SetActorRotation(TargetRotation);
	}
}
