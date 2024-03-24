// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/UseItemActor.h"

#include "Characters/ERCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/PackageComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Subsystem/ERSubsystem.h"

// Sets default values
AUseItemActor::AUseItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bShouldDelete = true;
	bIsLeaveMaster = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComponent->SetupAttachment(RootComponent);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	ProjectileMovementComponent->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void AUseItemActor::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

// Called every frame
void AUseItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUseItemActor::OnItemUsed(int32 ID)
{
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AUseItemActor::OnBeginOverlap);
}

void AUseItemActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}


void AUseItemActor::SetupMasterAndID(AERCharacterBase* Master, int32 ID)
{
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		if (FUseableItem* UseItem = reinterpret_cast<FUseableItem*>(ItemInfo))
		{
			ItemID = ID;
			MyMaster = Master;
			if (MyMaster->GetPackageComponent())
			{
				MyMaster->GetPackageComponent()->OnUseItem.AddUObject(this,&AUseItemActor::OnItemUsed);
			}
			if (UseItem->StaticMesh)
			{
				StaticMeshComponent->SetStaticMesh(UseItem->StaticMesh);
				return;
			}
			if (UseItem->SkeletalMesh)
			{
				SkeletalMeshComponent->SetSkeletalMesh(UseItem->SkeletalMesh);
				return;
			}
		}
	}
}

