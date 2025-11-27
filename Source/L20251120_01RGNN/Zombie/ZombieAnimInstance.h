// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZombieCharacter.h"
#include "ZombieAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class L20251120_01RGNN_API UZombieAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UZombieAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	float Speed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	EZombieState CurrentState = EZombieState::Normal;
};
