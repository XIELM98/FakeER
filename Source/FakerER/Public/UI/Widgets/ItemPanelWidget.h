// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UItemPanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void InitItemPanel();
	void UpdateUseItem(int32 ID);
	void UpdateSpell(int32 ID);
	void UpdateBattleAsh(int32 ID);
	void UpdateTalisman(int32 ID);
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemType;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemNum;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CostMana;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemEffect;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MemorySpaceText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MemorySpace;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NeedPower;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NeedAgile;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NeedIntelligence;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NeedBelief;
	UPROPERTY(meta=(BindWidget))
	class UImage* ItemIcon;
	

public:
	void UpdateItemPanel(int32);
	
};
