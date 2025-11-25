// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "MyTPC.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	int32 UnitX = Canvas->SizeX / 100;
	int32 UnitY = Canvas->SizeY / 100;
	int32 CenterX = Canvas->SizeX / 2;
	int32 CenterY = Canvas->SizeY / 2;

	int32 TargetSize = 4;

	AimResizeTimer += UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

	AMyTPC* BaseCharacter = Cast<AMyTPC>(GetOwningPawn());
	if (BaseCharacter)
	{
		GroundSpeed = BaseCharacter->GetCharacterMovement()->Velocity.Size2D();
		if (GroundSpeed > 600)
		{
			TargetSize = 12;
		}
		else if (GroundSpeed > 300)
		{
			TargetSize = 8;
		}
		else
		{
			TargetSize = 4;
		}
	}
	if(AimResizeTimer > 0.1f)
	{
		if (DrawSize < TargetSize)
		{
			++DrawSize;
		}
		else if (DrawSize > TargetSize)
		{
			--DrawSize;
		}
		AimResizeTimer = 0;
	}

	Draw2DLine(CenterX - (UnitX * DrawSize),
		CenterY,
		CenterX + (UnitX * DrawSize),
		CenterY,
		FColor(255, 0, 0, 0));

	Draw2DLine(CenterX,
		CenterY - (UnitY * DrawSize),
		CenterX,
		CenterY + (UnitY * DrawSize),
		FColor(255, 0, 0, 0));
}
