// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SceneItemsActor.h"

#include "ERHUD.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ERSubsystem.h"

// Sets default values
ASceneItemsActor::ASceneItemsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComponent->SetupAttachment(RootComponent);
	
	ID = -1;
	Num = 1;
}

// Called when the game starts or when spawned
void ASceneItemsActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ASceneItemsActor::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&ASceneItemsActor::OnBoxEndOverlap);

	Init(ID);
}

// Called every frame
void ASceneItemsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASceneItemsActor::Init(int32 InID)
{
	if (InID == -1)
	{
		return;
	}
		
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(InID))
	{
		ID = InID;
		if (ItemInfo->StaticMesh)
		{
			UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(this);
			StaticMeshComponent->RegisterComponentWithWorld(GetWorld());
			StaticMeshComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			StaticMeshComponent->SetStaticMesh(ItemInfo->StaticMesh);
		}
		if (ItemInfo->SkeletalMesh)
		{
			USkeletalMeshComponent* SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this);
			SkeletalMeshComponent->RegisterComponentWithWorld(GetWorld());
			SkeletalMeshComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			SkeletalMeshComponent->SetSkeletalMesh(ItemInfo->SkeletalMesh);
		}
	}
}

void ASceneItemsActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(OtherActor))
	{
		if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
		{
			HUD->ShowTips(NSLOCTEXT("HUD","PickUp","拾取"));
		}
		PlayerCharacter->SetNearItem(this);
	}
}

void ASceneItemsActor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(OtherActor))
	{
		if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
		{
			if (HUD->GetCurrentMenuPage() == EMenuPage::Main)
			{
				HUD->HideTips();
				PlayerCharacter->SetNearItem(nullptr);
			}
		}
	}
}

