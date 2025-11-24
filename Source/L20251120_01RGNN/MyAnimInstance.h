// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyTPC.h"

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class L20251120_01RGNN_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float GroundSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float Direction = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float AimYaw = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float AimPitch = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bLeftLean : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bRightLean : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bAiming : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float CurrentLeanAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	EWeaponState WeaponState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsCrouched : 1;
};
