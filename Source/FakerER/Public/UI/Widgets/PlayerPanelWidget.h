// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UPlayerPanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	void InitPlayerPanel();
	void SetSpells();
	FText GetEquipLevel(int32);
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Level;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HaveRune;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Red;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Blue;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Green;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Power;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Agile;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Intelligence;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Belief;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NowHP;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MaxHP;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NowMana;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MaxMana;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Endurance;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NowEquipWeight;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MaxEquipWeight;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* EquipmentLevel;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Toughness;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MemorySpace;
	UPROPERTY(meta=(BindWidget))
	class UWrapBox* Spells;

public:
	void UpdatePlayerPanel(int32 ID);
};
