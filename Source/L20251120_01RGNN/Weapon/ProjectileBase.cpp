// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameframeWork/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "BaseDamageType.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(10, 10, 5));
	Box->GetBodyInstance()->bNotifyRigidBodyCollision = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->MaxSpeed = 8000.0f;
	Movement->InitialSpeed = 8000.0f;

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	//OnActorBeginOverlap.AddDynamic(this, &AProjectileBase::ProcessBeginOverlap);
	//OnActorHit.AddDynamic(this, &AProjectileBase::ProcessOnActorHit);
	Box->OnComponentHit.AddDynamic(this, &AProjectileBase::ProcessOnComponentHit);
	SetLifeSpan(5.0f);
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//////RPG
	////UGameplayStatics::ApplyDamage(
	////	HitResult.GetActor(),
	////	50,
	////	GetController(),
	////	this,
	////	UBaseDamageType::StaticClass()
	////);
	////ÃÑ
	//UGameplayStatics::ApplyPointDamage(
	//	HitResult.GetActor(),
	//	50,
	//	-HitResult.ImpactNormal,
	//	HitResult,
	//	PC,
	//	this,
	//	UBaseDamageType::StaticClass()
	//);
	//////¹üÀ§, ÆøÅº
	////UGameplayStatics::ApplyRadialDamage(
	////	HitResult.GetActor(),
	////	50,
	////	HitResult.ImpactPoint,
	////	300.0f,
	////	UBaseDamageType::StaticClass(),
	////	IgnoreActors,
	////	this,
	////	GetController(),
	////	true
	////);
}

void AProjectileBase::ProcessOnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* OtherPawn = Cast<APawn>(OtherActor);
	if(OtherPawn != UGameplayStatics::GetPlayerController(GetWorld(),0)->GetPawn())
	{
		if (OtherPawn)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				BloodEffect,
				Hit.ImpactPoint,
				Hit.ImpactNormal.Rotation()
			);
		}
		else
		{
			UDecalComponent* MadeDecal = UGameplayStatics::SpawnDecalAtLocation(
				GetWorld(),
				Decal,
				FVector(5.0f, 5.0f, 5.0f),
				Hit.ImpactPoint,
				Hit.ImpactNormal.Rotation(),
				5.0f
			);

			MadeDecal->SetFadeScreenSize(0.005f);
		}
	}
	Destroy();
}

void AProjectileBase::ProcessOnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	SpawnHitEffect(Hit);

	APawn* Pawn = Cast<APawn>(GetOwner()->GetOwner());
	if(Pawn)
	{
		UGameplayStatics::ApplyPointDamage(
			HitResult.GetActor(),
			50,
			-HitResult.ImpactNormal,
			HitResult,
			Pawn->GetController(),
			this,
			UBaseDamageType::StaticClass()
		);
	}
	Destroy();
}

void AProjectileBase::SpawnHitEffect(FHitResult Hit)
{
	if(Decal)
	{
		UDecalComponent* MadeDecal = UGameplayStatics::SpawnDecalAtLocation(
			GetWorld(),
			Decal,
			FVector(5.0f, 5.0f, 5.0f),
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation(),
			5.0f
		);
		if(MadeDecal)
		{
			MadeDecal->SetFadeScreenSize(0.005f);
		}
	}
}

