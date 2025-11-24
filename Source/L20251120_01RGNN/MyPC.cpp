// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPC.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "MyTPC.h"

AMyPC::AMyPC()
{

}

void AMyPC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInput = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!IMC_Default.IsNull())
			{
				EnhancedInput->AddMappingContext(IMC_Default.LoadSynchronous(), 0);
			}
			if (!IMC_MouseLook.IsNull())
			{
				EnhancedInput->AddMappingContext(IMC_MouseLook.LoadSynchronous(), 0);
			}
		}
	}
}

void AMyPC::OnUnPossess()
{
	//TODO
	if (ULocalPlayer* LocalPlayer = Cast <ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInput = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!IMC_Default.IsNull())
			{
				EnhancedInput->RemoveMappingContext(IMC_Default.LoadSynchronous());
			}
			if (!IMC_MouseLook.IsNull())
			{
				EnhancedInput->RemoveMappingContext(IMC_MouseLook.LoadSynchronous());
			}
		}
	}
	Super::OnUnPossess();
}
