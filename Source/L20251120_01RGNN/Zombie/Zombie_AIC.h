// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieCharacter.h"
#include "Zombie_AIC.generated.h"

class UAIPerceptionComponent;
class UBehaviorTree;
/**
 * 
 */
UCLASS()
class L20251120_01RGNN_API AZombie_AIC : public AAIController
{
	GENERATED_BODY()
public:
	AZombie_AIC();

	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void OnUnPossess() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAIPerceptionComponent> Perception;

	UFUNCTION()
	void ProcessPerception(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void ProcessActorPerception(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void ProcessActorPerceptionForget(AActor* Actor);

	UFUNCTION()
	void ProcessActorPerceptionInfo(const FActorPerceptionUpdateInfo& UpdateInfo);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UBehaviorTree> RunBTAsset;

	void SetState(EZombieState NewState);
};
