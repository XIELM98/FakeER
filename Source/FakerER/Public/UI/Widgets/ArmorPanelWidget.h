// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmorPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UArmorPanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void InitArmorPanel();

protected:
	UPROPERTY(meta=(BindWidget))
	class UImage* ArmorIcon;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ArmorName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Weight;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PhysicalDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MagicDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* FireAttDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LightingAttDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* BloodingDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PoisonDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DeathDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ToughnessDefend;
	
	
public:
	void UpdateArmorPanel(int32);
};
