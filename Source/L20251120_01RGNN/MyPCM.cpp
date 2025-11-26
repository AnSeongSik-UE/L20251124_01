// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPCM.h"
#include "MyTPC.h"

AMyPCM::AMyPCM()
{
}

void AMyPCM::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	AMyTPC* Pawn = Cast<AMyTPC>(GetOwningPlayerController()->GetPawn());
	if (Pawn)
	{
		float TargetFOV = Pawn->bIsIronSight ? IronSightFOV : NormalFOV;
		float CurrentFOV = FMath::FInterpTo(GetFOVAngle(), TargetFOV, DeltaTime, ZoomSpeed);
		SetFOV(CurrentFOV);
		//UE_LOG(LogTemp, Warning, TEXT("%f"), GetFOVAngle());
	}
}
