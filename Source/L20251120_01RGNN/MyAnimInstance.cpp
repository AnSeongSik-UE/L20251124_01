// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyTPC.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "KismetAnimationLibrary.h"

UMyAnimInstance::UMyAnimInstance()
{
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	AMyTPC* Character = Cast<AMyTPC>(TryGetPawnOwner());
	if (Character)
	{
		GroundSpeed = Character->GetCharacterMovement()->Velocity.Size2D();
		Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetCharacterMovement()->Velocity, Character->GetActorRotation());
		AimYaw = Character->GetBaseAimRotation().Yaw;
		AimPitch = Character->GetBaseAimRotation().Pitch;
		bLeftLean = Character->bLeftLean;
		bRightLean = Character->bRightLean;
		bAiming = Character->bAiming;
		
		float TargetLeanAngle = 0;
		if (bLeftLean)
		{
			TargetLeanAngle = -30.0f;
		}
		else if (bRightLean)
		{
			TargetLeanAngle = 30.0f;
		}
		else
		{
			TargetLeanAngle = 0;
		}

		CurrentLeanAngle = FMath::FInterpTo(CurrentLeanAngle, TargetLeanAngle, DeltaSeconds, 8.0f);

		WeaponState = Character->WeaponState;

		bIsCrouched = Character->bIsCrouched;

		bIsFalling = Character->GetCharacterMovement()->IsFalling();
	}
	
}
