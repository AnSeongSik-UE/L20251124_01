// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Attack.h"
#include "Zombie/ZombieCharacter.h"

UAnimNotify_Attack::UAnimNotify_Attack()
{
}

FString UAnimNotify_Attack::GetNotifyName_Implementation() const
{
	return FString(TEXT("Attack"));
}

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AZombieCharacter* Zombie = Cast<AZombieCharacter>(MeshComp->GetOwner());
	if (Zombie)
	{
		EventReference.
	}
}
