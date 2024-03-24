// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponPanelWidget.generated.h"

enum class EAbnormalState : uint8;
/**
 * 
 */
UCLASS()
class FAKEER_API UWeaponPanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	FText GetAbnormalText(EAbnormalState State,int32 Num);
	void InitWeaponPanel();
	FText CalAdditionLevel(int32 Num);

	
protected:

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* WeaponName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponType;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* BattleAshName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CostMana;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponWeight;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PhysicalAttack;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PhysicalCalculate;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PhysicalAdditionAttack;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MagicAttack;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MagicCalculate;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MagicAdditionAttack;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* FireAttack;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* FireCalculate;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* FireAdditionAttack;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LightingAttack;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LightingCalculate;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LightingAdditionAttack;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ExecuteNum;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PhysicalDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MagicDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* FireDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LightingDefend;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DefendStrength;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AdditionPower;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AdditionAgile;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AdditionIntelligence;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AdditionBelief;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NeedPower;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NeedAgile;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NeedIntelligence;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NeedBelief;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AbnormalState1;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AbnormalState2;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AbnormalState3;
	UPROPERTY(meta=(BindWidget))
	class UImage* WeaponIcon;

	
public:
	void UpdateWeaponPanel(int32 ID);
	
};
