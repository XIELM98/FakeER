// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/ERSubsystem.h"
#include "Widgets/GridWidget.h"

#include "EquipUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UEquipUserWidget : public UUserWidget
{
	GENERATED_BODY()
	friend class UPackageComponent;
	
protected:

	virtual void NativeOnInitialized() override;
	
	void CreateGrids();
	void CreateWeapons();
	void CreateOthers();

	void UpdateWeaponPanel(int32 ID);
	void UpdateUseItemPanel(int32 ID);
	void UpdateArmorPanel(int32 ID);
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* RightWeapon1;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* RightWeapon2;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* RightWeapon3;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* LeftWeapon1;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* LeftWeapon2;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* LeftWeapon3;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* Arrow1;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* Arrow2;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* Bolt1;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* Bolt2;
	
	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* Armor;
	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* Talisman;
	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* Item1;
	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* Item2;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* GridPos;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta=(BindWidget))
	class UPlayerPanelWidget* PlayerPanelWidget;
	UPROPERTY(meta=(BindWidget))
	class UWeaponPanelWidget* WeaponPanelWidget;
	UPROPERTY(meta=(BindWidget))
	class UArmorPanelWidget* ArmorPanelWidget;
	UPROPERTY(meta=( BindWidget))
	class UItemPanelWidget* ItemPanelWidget;
	UPROPERTY(meta=(BindWidget))
	class UItemWidget* ItemWidget;
	UPROPERTY()
	TArray<UGridWidget*>AllGrids;
	
	UPROPERTY()
    class AERHUD* HUD;
    UPROPERTY()
    class UGridWidget* ChooseGrid;
public:
	void SetGridInfo(FText InGridPos,FText InItemName);
	void ChooseItem(EItemType,EArmorType InArmorType = EArmorType::Helmet);
	void SetChooseGrid(UGridWidget* NewGrid) {ChooseGrid = NewGrid;}
	UGridWidget* GetChooseGrid() const {return ChooseGrid;}
	void BindChooseGrid(int32 ID);
	void CloseItemWidget();
	void SetItemName(FText InItemName);
	void UpdatePlayerPanelWidget(int32 ID);
	void UpdatePanelWidget(int32 ID);
	
};


