// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Attack.generated.h"

/**
 * 
 */
UCLASS()
class L20251120_01RGNN_API UAnimNotify_Attack : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_Attack();

	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
