// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPCM.h"
#include "MyTPC.h"

#include "Kismet/KismetMathLibrary.h"

AMyPCM::AMyPCM()
{
}

void AMyPCM::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	AMyTPC* Pawn = Cast<AMyTPC>(GetOwningPlayerController()->GetPawn());
	if (Pawn)
	{
		if (Pawn->bIsIronSight)
		{
			SetFOV(UKismetMathLibrary::FInterpTo(GetFOVAngle(), 60.0f, DeltaTime, 5.0f));
		}
		else
		{
			SetFOV(UKismetMathLibrary::FInterpTo(GetFOVAngle(), 90.0f, DeltaTime, 5.0f));
		}
		//UE_LOG(LogTemp, Warning, TEXT("%f"), GetFOVAngle());
	}
}
