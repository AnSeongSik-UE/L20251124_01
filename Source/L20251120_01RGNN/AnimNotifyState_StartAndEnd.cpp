// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_StartAndEnd.h"

FString UAnimNotifyState_StartAndEnd::GetNotifyName_Implementation() const
{
	return TEXT("StartAndEnd");
}

void UAnimNotifyState_StartAndEnd::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	UE_LOG(LogTemp, Warning, TEXT("NotifyBegin"));
}

void UAnimNotifyState_StartAndEnd::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("NotifyTick"));
}

void UAnimNotifyState_StartAndEnd::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UE_LOG(LogTemp, Warning, TEXT("NotifyEnd"));
	Super::NotifyEnd(MeshComp, Animation);
}
