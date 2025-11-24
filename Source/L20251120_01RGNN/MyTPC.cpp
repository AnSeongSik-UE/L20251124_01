// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTPC.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ChildActorComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"

#include "Weapon/WeaponBase.h"

// Sets default values
AMyTPC::AMyTPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -89.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, 270.0f, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm);

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AMyTPC::BeginPlay()
{
	Super::BeginPlay();

	//무기 집으면 잡게 이동
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
	}
	
}

// Called every frame
void AMyTPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyTPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Reload, ETriggerEvent::Completed, this, &AMyTPC::Reload);
	}
}

void AMyTPC::Movement(float InX, float InY)
{
	const FRotator CameraRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0, CameraRotation.Yaw, 0);
	const FRotator YawRollRotation = FRotator(0, CameraRotation.Yaw, CameraRotation.Roll);

	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRollRotation);
	AddMovementInput(ForwardVector, InX);

	const FVector RightVector = UKismetMathLibrary::GetRightVector(YawRotation);
	AddMovementInput(RightVector, InY);
}

void AMyTPC::Look(float InX, float InY)
{
	AddControllerPitchInput(InX);
	AddControllerYawInput(InY);
}

void AMyTPC::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 1500;
}

void AMyTPC::Jog()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AMyTPC::Reload()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		PlayAnimMontage(ChildWeapon->ReloadMontage);
	}
}

void AMyTPC::HitReaction()
{
	FString SectionName = FString::Printf(TEXT("%d"), FMath::RandRange(1, 8));

	PlayAnimMontage(HitMontage, 1.0f, FName(*SectionName));
}

void AMyTPC::ReloadWeapon()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->Reload();
	}
}

