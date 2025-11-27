// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameframeWork/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(10, 10, 5));

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
	OnActorBeginOverlap.AddDynamic(this, &AProjectileBase::ProcessBeginOverlap);
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	AActor* OtherPawn = Cast<APawn>(OtherActor);
	if (OtherPawn)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			BloodEffect,
			HitResult.ImpactPoint,
			HitResult.ImpactNormal.Rotation()
		);
	}

	UDecalComponent* MadeDecal = UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),
		Decal,
		FVector(5.0f,5.0f,5.0f),
		HitResult.ImpactPoint,
		HitResult.ImpactNormal.Rotation(),
		5.0f
		);

	MadeDecal->SetFadeScreenSize(0.005f);

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

