// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPNow;
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HPChanging;
	
	// UPROPERTY()
	// class AERCharacterBase* Owner;
	float NowPercent;
	float BeforePercent;
	float TempPercent;
	
	void SetHPChanging();
	void HPChangingStart();
	void HPNowStart();

	FTimerHandle DamageTimerHandle;
	FTimerHandle HPNowTimeHandle;
	FTimerHandle HPChangingTimerHandle;
	
public:
	//void SetOwner(AERCharacterBase* InOwner) {Owner = InOwner;}
	void AddHealth(float NewPercent);
	void LoseHealth(float NewPercent);
	
};

