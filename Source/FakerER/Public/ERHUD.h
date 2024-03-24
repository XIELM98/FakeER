// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ERHUD.generated.h"

/**
 * 
 */

enum class EUseItemType : uint8;
enum class EItemType : uint8;

UENUM()
enum class EMenuPage : uint8
{
	Main,
	Menu,
	Package,
	Equip,
	Rest,
	State,
	Config,
	Tips,
	ChooseItem,
	Talk,
	Shop
};

USTRUCT()
struct FPackageOption
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UTexture2D* OptionIcon;
	UPROPERTY(EditAnywhere)
	EItemType ItemType;
	UPROPERTY(EditAnywhere)
	EUseItemType UseItemType;
	UPROPERTY(EditAnywhere)
	float Translation;
	UPROPERTY(EditAnywhere)
	bool bIsAll;
	bool operator== ( FPackageOption NewPackageOption) const
	{
		if (OptionIcon == NewPackageOption.OptionIcon &&
		ItemType == NewPackageOption.ItemType &&
		UseItemType == NewPackageOption.UseItemType&&
		Translation == NewPackageOption.Translation &&
		bIsAll == NewPackageOption.bIsAll)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void operator=(FPackageOption NewPackageOption) 
	{
		OptionIcon = NewPackageOption.OptionIcon;
		ItemType = NewPackageOption.ItemType;
		UseItemType = NewPackageOption.UseItemType;
		Translation = NewPackageOption.Translation;
		bIsAll = NewPackageOption.bIsAll;
	}
};


UCLASS()
class FAKEER_API AERHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

protected:
	
	UPROPERTY(EditAnywhere)
	class UMenuUserWidget* MenuUserWidget;
	UPROPERTY(EditAnywhere)
	class UMainUserWidget* MainUI;
	UPROPERTY(EditAnywhere)
	class URestUserWidget* RestUserWidget;
	UPROPERTY(EditAnywhere)
	class UTipsWidget* TipsWidget;
	UPROPERTY(EditAnywhere)
	class UPickUpWidget* PickUpWidget;
	
	EMenuPage CurrentMenuPage;
	
public:
	void HideMenu();
	void ShowMenu();
	void ToggleMenu();
	void ToggleRestUI();
	
	EMenuPage GetCurrentMenuPage() const{return CurrentMenuPage;}
	void SetCurrentMenuPage(EMenuPage NewPage){CurrentMenuPage = NewPage;}
	
	UMenuUserWidget* GetMenuUserWidget() const { return  MenuUserWidget;}
	UMainUserWidget* GetMainUserWidget() const { return  MainUI;}
	
	void HideTips();
	void ShowTips(FText ShowText);

	void ShowPickUpUI(int32 ,int32 );
	void HidePickUpUI();

public:
	//BG
	UPROPERTY(EditAnywhere)
	UTexture2D* EquipBGImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* PackageBGImage;

	
	//Equip
	UPROPERTY(EditAnywhere)
	UTexture2D* AllItemImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* WeaponImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* ShieldImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* ArrowImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* BoltImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* HelmetImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* BodyImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* HandImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* FootImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* TalismanImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* ItemImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* SpellImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* KeyImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* BattleAshImage;


	//Keys
	UPROPERTY(EditAnywhere)
	UTexture2D* KeyboardE;
	UPROPERTY(EditAnywhere)
	UTexture2D* KeyboardQ;
};
