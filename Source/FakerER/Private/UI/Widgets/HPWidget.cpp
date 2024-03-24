// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/HPWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"


void UHPWidget::NativeConstruct()
{
	NowPercent = 1.f;
	BeforePercent = 1.f;
	TempPercent = 1.f;
	HPChanging->SetPercent(1.0f);
	HPChanging->SetVisibility(ESlateVisibility::Visible);
	HPNow->SetPercent(1.0f);
	HPNow->SetVisibility(ESlateVisibility::Visible);
	Super::NativeConstruct();
}


void UHPWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UHPWidget::SetHPChanging()
{
	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	//TempPercent = BeforePercent;
	GetWorld()->GetTimerManager().SetTimer(HPChangingTimerHandle,this,&UHPWidget::HPChangingStart,0.05,true);
}

void UHPWidget::HPChangingStart()
{
	if (BeforePercent == NowPercent)
	{
		UE_LOG(LogTemp,Log,TEXT("Over"))
		GetWorld()->GetTimerManager().ClearTimer(HPChangingTimerHandle);
	}
	BeforePercent = UKismetMathLibrary::FInterpTo_Constant(BeforePercent,NowPercent,0.05,2);
	HPChanging->SetPercent(BeforePercent);
}

void UHPWidget::HPNowStart()
{
	if (BeforePercent == NowPercent)
	{
		UE_LOG(LogTemp,Log,TEXT("Over"))
		GetWorld()->GetTimerManager().ClearTimer(HPNowTimeHandle);
	}
	NowPercent = UKismetMathLibrary::FInterpTo_Constant(BeforePercent,NowPercent,0.05,2);
	HPNow->SetPercent(NowPercent);
}

void UHPWidget::AddHealth(float NewPercent)
{
	BeforePercent = NewPercent;
	HPChanging->SetPercent(NowPercent);
	GetWorld()->GetTimerManager().SetTimer(HPNowTimeHandle,this,&UHPWidget::SetHPChanging,0.05f,true);
}

void UHPWidget::LoseHealth(float NewPercent)
{
	NowPercent = NewPercent;
	HPNow->SetPercent(NowPercent);
	if (GetWorld()->GetTimerManager().IsTimerPending(HPChangingTimerHandle))
	{
		BeforePercent = NowPercent;
		GetWorld()->GetTimerManager().ClearTimer(HPChangingTimerHandle);
	}
	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle,this,&UHPWidget::SetHPChanging,1.f,false);
}




