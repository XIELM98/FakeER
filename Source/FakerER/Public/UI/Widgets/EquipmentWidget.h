// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
protected:
	virtual void NativeOnInitialized() override;

	
	void InitGrids();
	void ChangeSpell();
	void ChangeItem();
	void ChangeLeftWeapon();
	void ChangeRightWeapon();
	void UnEquipLeftWeapon();
	void UnEquipRightWeapon();
	void EquipLeftWeapon();
	void EquipRightWeapon();

	void SetUpItemArray();
	void SetUpItems();
	void SetUpSpell();

	void OnEquip(int32 ID);
	void OnUnEquip(int32 ID);
	void OnUseItem(int32 ID);
	
	void SetUpWeapon();
	
	void BindGridItemAndNum(class UGridWidget* Grid,int32 ID);
	

protected:
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* RightWeapon;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* LeftWeapon;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* Spell;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* NextSpell1;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* NextSpell2;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* Item;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* NextItem1;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* NextItem2;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* SpellName;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemName;
	
	UPROPERTY()
	class UTexture2D* EquipmentBG;


	TArray<int32> ItemArray;
	TArray<int32> RightWeaponIDArray;
	TArray<int32> LeftWeaponIDArray;
	
public:
	int32 GetEquipItem();
	int32 GetRightWeaponArrayNum() const {return RightWeaponIDArray.Num();}
};



