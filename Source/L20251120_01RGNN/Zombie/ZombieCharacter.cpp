// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"
#include "Engine/DamageEvents.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AZombieCharacter::AZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//APawn* TargetPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

	//FRotator ZombieDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPawn->GetActorLocation());

	//AddMovementInput(TargetPawn->GetActorLocation() - GetActorLocation());
	//SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), ZombieDirection, DeltaTime, 5.f));
}

void AZombieCharacter::SetState(EZombieState NewState)
{
	CurrentState = NewState;
}

float AZombieCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentHP <= 0)
	{
		return Damage;
	}

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* Event = (FPointDamageEvent*)(&DamageEvent);
		if (Event)
		{
			CurrentHP -= Damage;
			UE_LOG(LogTemp, Warning, TEXT("Point Damage %f %s"), Damage, *Event->HitInfo.BoneName.ToString());
		}
		SpawnHitEffect(Event->HitInfo);
	}
	else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* Event = (FRadialDamageEvent*)(&DamageEvent);
		if (Event)
		{
			CurrentHP -= Damage;
			UE_LOG(LogTemp, Warning, TEXT("Radial Damage %f %s"), Damage, *Event->DamageTypeClass->GetName());
		}
	}
	else //(DamageEvent.IsOfType(FDamageEvent::ClassID)) 먼저 if하면 FDamageEvent로 덮어씌워버림
	{
		CurrentHP -= Damage;
		UE_LOG(LogTemp, Warning, TEXT("Damage %f"), Damage);
	}

	if (CurrentHP <= 0)
	{
		DoDead();
	}

	return Damage;
}

void AZombieCharacter::DoDeadEnd()
{
	GetController()->SetActorEnableCollision(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AZombieCharacter::DoDead()
{
	//PlayAnimMontage(DeathMontage, 1.0f, DeathSections[UKismetMathLibrary::RandomIntegerInRange(0, 5)]);
}

void AZombieCharacter::SpawnHitEffect(FHitResult Hit)
{
	if (BloodEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			BloodEffect,
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation()
		);
	}
}
