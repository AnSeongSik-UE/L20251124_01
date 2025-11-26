// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTPC.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ChildActorComponent.h"
#include "EnhancedInputComponent.h"
#include "Weapon/WeaponBase.h"
#include "Weapon/BaseDamageType.h"
#include "Engine/DamageEvents.h"
#include "PickupItemBase.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

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

	DeathSections.Add("Back_01");
	DeathSections.Add("Front_01");
	DeathSections.Add("Front_02");
	DeathSections.Add("Front_03");
	DeathSections.Add("Left_01");
	DeathSections.Add("Right_01");
}

// Called when the game starts or when spawned
void AMyTPC::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMyTPC::ProcessBeginOverlap);
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

		UIC->BindAction(IA_Fire, ETriggerEvent::Started, this, &AMyTPC::StartFire);
		UIC->BindAction(IA_Fire, ETriggerEvent::Completed, this, &AMyTPC::StopFire);
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

void AMyTPC::DoFire()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->Fire();
	}
}

void AMyTPC::StartFire()
{
	bIsFire = true;
	DoFire();
}

void AMyTPC::StopFire()
{
	bIsFire = false;
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->StopFire();
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

float AMyTPC::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if(CurrentHP > 0.0f )
	{
		if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
		{
			FPointDamageEvent* Event = (FPointDamageEvent*)(&DamageEvent);
			if (Event)
			{
				CurrentHP -= Damage;
				UE_LOG(LogTemp, Warning, TEXT("Point Damage %f %s"), Damage, *Event->HitInfo.BoneName.ToString());
			}
		}
		else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
		{
			FRadialDamageEvent* Event = (FRadialDamageEvent*)(&DamageEvent);
			if (Event)
			{
				CurrentHP -= Damage;
				UE_LOG(LogTemp, Warning, TEXT("Radial Damage %f %s"), Damage, *Event->DamageTypeClass->GetName());
			}
		}
		else //(DamageEvent.IsOfType(FDamageEvent::ClassID)) 먼저 if하면 FDamageEvent로 덮어씌워버림
		{
			CurrentHP -= Damage;
			UE_LOG(LogTemp, Warning, TEXT("Damage %f"), Damage);
		}
		DoHitReact();
	}

	if (CurrentHP <= 0.0f)
	{
		DoDead();
	}

	return Damage;
}

void AMyTPC::DoDeadEnd()
{
	GetController()->SetActorEnableCollision(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AMyTPC::DoDead()
{
	PlayAnimMontage(DeathMontage, 1.0f, DeathSections[UKismetMathLibrary::RandomIntegerInRange(0, 5)]);
}

void AMyTPC::DoHitReact()
{
	PlayAnimMontage(HitMontage, 1.0f, (FName)*FString::FromInt(UKismetMathLibrary::RandomIntegerInRange(1, 8)));
}

void AMyTPC::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	APickupItemBase* PickedUpItem = Cast<APickupItemBase>(OtherActor);

	if (PickedUpItem)
	{
		//FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = this;
		//SpawnParams.Instigator = this;
		//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

		//장작하는 아이템, 먹는거냐, 사용하는거냐?
		switch (PickedUpItem->ItemType)
		{
		case EItemType::Use:
			UseItem(PickedUpItem);
			break;
		case EItemType::Eat:
			EatItem(PickedUpItem);
			break;
		case EItemType::Equip:
			EquipItem(PickedUpItem);
			break;
		}

		if(!PickedUpItem->bIsInfinity)
		{
			PickedUpItem->Destroy();
		}
	}
}

void AMyTPC::UseItem(APickupItemBase* PickedUpItem)
{
}

void AMyTPC::EatItem(APickupItemBase* PickedUpItem)
{
}

void AMyTPC::EquipItem(APickupItemBase* PickedUpItem)
{
	Weapon->SetChildActorClass(PickedUpItem->ItemTemplate);
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		if (ChildWeapon->Name.Compare(TEXT("Pistol")) == 0)
		{
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			WeaponState = EWeaponState::Pistol;
			ChildWeapon->SetOwner(this);
		}
		else if (ChildWeapon->Name.Compare(TEXT("Rifle")) == 0)
		{
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			WeaponState = EWeaponState::Rifle;
			ChildWeapon->SetOwner(this);
		}
	}
}