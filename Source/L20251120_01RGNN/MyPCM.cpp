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
		if (Pawn->bIsIronSight)
		{
			SetFOV(60.0f);
		}
		else
		{
			SetFOV(90.0f);
		}
	}
}
