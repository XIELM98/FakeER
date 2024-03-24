// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractActor.h"

#include "ERHUD.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractActor::AInteractActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AInteractActor::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this,&AInteractActor::OnBoxEndOverlap);
}

// Called every frame
void AInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(OtherActor))
	{
		if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
		{
			HUD->ShowTips(NSLOCTEXT("HUD","PickUp","互动"));
		}
		PlayerCharacter->SetNearActor(this);
	}
}

void AInteractActor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(OtherActor))
	{
		if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
		{
			if (HUD->GetCurrentMenuPage() == EMenuPage::Main)
			{
				HUD->HideTips();
				PlayerCharacter->SetNearActor(nullptr);
			}
		}
	}
}
