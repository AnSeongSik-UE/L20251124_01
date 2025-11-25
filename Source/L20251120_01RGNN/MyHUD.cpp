// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "MyTPC.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	int32 Unit = Canvas->SizeX / 100;
	int32 CenterX = Canvas->SizeX / 2;
	int32 CenterY = Canvas->SizeY / 2;

	int32 DrawSize = Unit * 2;

	float CurrentSpeed = 0.0f;
	float MaxSpeed = 0.0f;
	float GapRatio = 0.0f;
	int32 Gap = Unit * 3;

	AMyTPC* BaseCharacter = Cast<AMyTPC>(GetOwningPawn());
	if (BaseCharacter)
	{
		MaxSpeed = BaseCharacter->GetCharacterMovement()->GetMaxSpeed();
		CurrentSpeed = BaseCharacter->GetCharacterMovement()->Velocity.Size2D();
		GapRatio = CurrentSpeed / MaxSpeed;

	}

	Gap = (int32)((float)Gap * GapRatio);

	//LeftX
	Draw2DLine(CenterX - DrawSize - Gap,
		CenterY,
		CenterX - Gap,
		CenterY,
		FColor(255, 0, 0, 0));
	//RightX
	Draw2DLine(CenterX + DrawSize + Gap,
		CenterY,
		CenterX + Gap,
		CenterY,
		FColor(255, 0, 0, 0));
	//UpY
	Draw2DLine(CenterX,
		CenterY - DrawSize - Gap,
		CenterX,
		CenterY - Gap,
		FColor(255, 0, 0, 0));
	//ButtomY
	Draw2DLine(CenterX,
		CenterY + DrawSize + Gap,
		CenterX,
		CenterY + Gap,
		FColor(255, 0, 0, 0));
}
