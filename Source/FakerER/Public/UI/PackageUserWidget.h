// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ERHUD.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PackageUserWidget.generated.h"

struct FPackageOption;
/**
 * 
 */
UCLASS()
class FAKEER_API UPackageUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	void SpawnPackageOptions();
	void UpdateArmorPanel(int32 ID);
	void UpdateUseItemPanel(int32 ID);
	void UpdateWeaponPanel(int32 ID);
	UFUNCTION()
	void NextGrid();
	UFUNCTION()
	void BeforeGrid();
	
protected:
	UPROPERTY()
	AERHUD* HUD;
	UPROPERTY(EditAnywhere)
	TArray<FPackageOption> PackageOptions;
	UPROPERTY()
	TArray<class UGridWidget*>GridArray;
	UPROPERTY()
	TMap<UGridWidget*,FPackageOption> PackageInfoMap;
	UPROPERTY()
	UGridWidget* NowGrid;

	
	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* PackageHorizontalBox;
	UPROPERTY(meta=(BindWidget))
	UGridWidget* Before;
	UPROPERTY(meta=(BindWidget))
	UGridWidget* Next;
	UPROPERTY(meta=(BindWidget))
	class UItemWidget* ItemWidget;
	UPROPERTY(meta=(BindWidget))
	class UItemPanelWidget* ItemPanelWidget;
	UPROPERTY(meta=(BindWidget))
	class UWeaponPanelWidget* WeaponPanelWidget;
	UPROPERTY(meta=(BindWidget))
	class UArmorPanelWidget* ArmorPanelWidget;
	UPROPERTY(meta=(BindWidget))
	class UPlayerPanelWidget* PlayerPanelWidget;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemType;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* ChooseBGImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* UnChooseBGImage;
	
public:
	void SetItems(UGridWidget* Grid);
	
	void UpdatePanel(int32 ID);
	
	// UPROPERTY(meta=(BindWidget))
	// class UWidgetSwitcher* ItemWidgetSwitcher;
	// UPROPERTY(meta=(BindWidget))
	// UGridWidget* AllItem;
	// UPROPERTY(meta=(BindWidget))
	// UGridWidget* UseItem;
	// UPROPERTY(meta=(BindWidget))
	// UGridWidget* Weapon;
	// UPROPERTY(meta=(BindWidget))
	// UGridWidget* Armor;
	// UPROPERTY(meta=(BindWidget))
	// UGridWidget* KeyItem;
	// UPROPERTY(meta=(BindWidget))
	// UGridWidget* Arrow;
	// UPROPERTY(meta=(BindWidget))
	// UGridWidget* Bolt;
	// UPROPERTY(meta=(BindWidget))
	// UGridWidget* Spell;
	// UPROPERTY(meta=(BindWidget))
	// UGridWidget* BattleAsh;
	// UPROPERTY(meta=(BindWidget))
	// UGridWidget* Talisman;
	
};
