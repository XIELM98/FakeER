// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/EREnemyBase.h"

#include "Components/WidgetComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/HPWidget.h"

// Sets default values
AEREnemyBase::AEREnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPComponent"));
	HPWidgetComponent->SetupAttachment(RootComponent);
	HPWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HPWidgetComponent->SetVisibility(true);
	HPWidgetComponent->SetDrawSize(FVector2d(120.f,20.f));

}


// Called when the game starts or when spawned
void AEREnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (!HPWidgetClass)
	{
		HPWidgetClass = LoadClass<UHPWidget>(this,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_HP.WBP_HP_C'"));
	}
	
	HPWidgetComponent->SetWidgetClass(HPWidgetClass);
	if (!HPWidget)
	{
		HPWidget = Cast<UHPWidget>(HPWidgetComponent->GetUserWidgetObject());
	}
}

float AEREnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (HitSound)
	{
		FHitResult HitResult;
		FVector Impulse;
		DamageEvent.GetBestHitInfo(this,DamageCauser,HitResult,Impulse);
		UGameplayStatics::PlaySoundAtLocation(this,HitSound,HitResult.Location,GetActorRotation());
	}

	HPWidget->LoseHealth(CharacterPanel.NowHP / CharacterPanel.MaxHP);
	
	return 0;
}

// Called every frame
void AEREnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

