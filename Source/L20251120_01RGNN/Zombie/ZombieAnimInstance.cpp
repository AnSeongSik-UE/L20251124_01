// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ZombieCharacter.h"

UZombieAnimInstance::UZombieAnimInstance()
{

}

void UZombieAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AZombieCharacter* Character = Cast<AZombieCharacter>(TryGetPawnOwner());
	if (Character)
	{
		Speed = Character->GetCharacterMovement()->Velocity.Size2D();
		CurrentState = Character->CurrentState;
	}
}
