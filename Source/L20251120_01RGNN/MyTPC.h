// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "MyTPC.generated.h"

class UInputAction;
class UAnimMontage;
class UAIPerceptionStimuliSourceComponent;

UENUM(BlueprintType)
enum class EWeaponState :uint8
{
	Unarmed = 0 UMETA(DisplayName = "Unarmed"),
	Pistol = 10 UMETA(DisplayName = "Pistol"),
	Rifle = 20 UMETA(DisplayName = "Rifle"),
	Launcher = 30 UMETA(DisplayName = "Launcher")
};

UCLASS()
class L20251120_01RGNN_API AMyTPC : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyTPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UChildActorComponent> Weapon;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TObjectPtr<UAIPerceptionStimuliSourceComponent> StimuliSource;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Movement(float InX, float InY);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Look(float InX, float InY);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Sprint();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Jog();

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void DoFire();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bLeftLean : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bRightLean : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bAiming : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	EWeaponState WeaponState = EWeaponState::Unarmed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TObjectPtr<UInputAction> IA_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TObjectPtr<UInputAction> IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TObjectPtr<UInputAction> IA_IronSight;

	UFUNCTION(BlueprintCallable)
	void HitReaction();

	UFUNCTION(BlueprintCallable)
	void ReloadWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float CurrentHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxHP = 100;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnHitEffect(FHitResult Hit);

	TArray<FName> DeathSections;

	UFUNCTION(BlueprintCallable)
	void DoDeadEnd();

	UFUNCTION(BlueprintCallable)
	void DoDead();

	UFUNCTION(BlueprintCallable)
	void DoHitReact();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsFire : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsIronSight : 1 = false;

	UFUNCTION()
	void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void UseItem(class APickupItemBase* PickedUpItem);

	void EatItem(class APickupItemBase* PickedUpItem);

	void EquipItem(class APickupItemBase* PickedUpItem);

	void StartIronSight();

	void StopIronSight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UParticleSystem> BloodEffect;

	//----------------------------------------------------------------------//
	// IGenericTeamAgentInterface
	//----------------------------------------------------------------------//
	FGenericTeamId TeamID;
	/** Assigns Team Agent to given TeamID */
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;

	/** Retrieve team identifier in form of FGenericTeamId */
	virtual FGenericTeamId GetGenericTeamId() const override;
};
