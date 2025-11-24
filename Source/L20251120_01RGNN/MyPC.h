// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPC.generated.h"

/**
 * 
 */
UCLASS()
class L20251120_01RGNN_API AMyPC : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TSoftObjectPtr<class UInputMappingContext> IMC_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TSoftObjectPtr<class UInputMappingContext> IMC_MouseLook;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
};
