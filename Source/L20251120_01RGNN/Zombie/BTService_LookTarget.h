// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LookTarget.generated.h"

/**
 * 
 */
UCLASS()
class L20251120_01RGNN_API UBTService_LookTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_LookTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
