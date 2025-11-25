// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Death.h"
#include "MyTPC.h"

FString UAnimNotify_Death::GetNotifyName_Implementation() const
{
	return TEXT("Death");
}

void UAnimNotify_Death::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AMyTPC* BaseCharacter = Cast<AMyTPC>(MeshComp->GetOwner());
	if(BaseCharacter)
	{
		BaseCharacter->DoDeadEnd();
	}
}
