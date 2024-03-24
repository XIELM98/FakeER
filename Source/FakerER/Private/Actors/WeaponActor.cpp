// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WeaponActor.h"

#include "Characters/ERCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DamageEvents.h"
#include "Subsystem/ERSubsystem.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	WeaponCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCapsulComp"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMeshComp"));

	WeaponCapsuleComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCapsuleComponent->SetCollisionProfileName(TEXT("Weapon"));
	
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	WeaponCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this,&AWeaponActor::OnWeaponOverlap);
}

void AWeaponActor::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsDamageEnable)
	{
		return;
	}
	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(OtherActor))
	{
		if (CharacterBase == MyMaster)
		{
			return;
		}
		FPointDamageEvent DamageEvent;
		DamageEvent.HitInfo = SweepResult;
		CharacterBase->TakeDamage(1,DamageEvent,CharacterBase->GetController(),this);
		bIsDamageEnable = false;
	}
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponActor::SetupMasterAndID(AERCharacterBase* Master, int32 ID)
{
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		if (FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo))
		{
			ItemID = ID;
			MyMaster = Master;
			if (WeaponInfo->StaticMesh)
			{
				StaticMeshComponent->SetStaticMesh(WeaponInfo->StaticMesh);
				return;
			}
			if (WeaponInfo->SkeletalMesh)
			{
				SkeletalMeshComponent->SetSkeletalMesh(WeaponInfo->SkeletalMesh);
				return;
			}
		}
	}
}


