// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyTPC.generated.h"

UENUM(BlueprintType)
enum class EWeaponState :uint8
{
	Unarmed = 0 UMETA(DisplayName = "Unarmed"),
	Pistol = 10 UMETA(DisplayName = "Pistol"),
	Rifle = 20 UMETA(DisplayName = "Rifle"),
	Launcher = 30 UMETA(DisplayName = "Launcher")
};

UCLASS()
class L20251120_01RGNN_API AMyTPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyTPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Movement(float InX, float InY);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Look(float InX, float InY);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Sprint();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Jog();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bLeftLean : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bRightLean : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bAiming : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	EWeaponState WeaponState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TObjectPtr<UAnimMontage> DeathMontage;
};
