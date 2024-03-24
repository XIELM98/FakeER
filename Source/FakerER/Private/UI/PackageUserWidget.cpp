// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PackageUserWidget.h"

#include "ERHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/PackageComponent.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ERSubsystem.h"
#include "UI/Widgets/ArmorPanelWidget.h"
#include "UI/Widgets/GridWidget.h"
#include "UI/Widgets/ItemPanelWidget.h"
#include "UI/Widgets/ItemWidget.h"
#include "UI/Widgets/WeaponPanelWidget.h"


void UPackageUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD());

	SpawnPackageOptions();
	
	Before->SetIcon(HUD->KeyboardQ);
	Next->SetIcon(HUD->KeyboardE);
	Before->GetButton()->OnClicked.AddDynamic(this,&UPackageUserWidget::BeforeGrid);
	Next->GetButton()->OnClicked.AddDynamic(this,&UPackageUserWidget::NextGrid);
	if (PackageInfoMap.Num() >= 0)
	{
		NowGrid = PackageInfoMap.begin().Key();
		SetItems(NowGrid);
	}
}


void UPackageUserWidget::SpawnPackageOptions()
{
	for (auto Key : PackageOptions)
	{
		TSubclassOf<UGridWidget> GridClass = LoadClass<UGridWidget>(this,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_Grid.WBP_Grid_C'"));
		USizeBox* SizeBox = NewObject<USizeBox>(this);
		UGridWidget* Grid = CreateWidget<UGridWidget>(this,GridClass);
		SizeBox->SetHeightOverride(80);
		SizeBox->SetWidthOverride(80);
		SizeBox->AddChild(Grid);
		Grid->SetIcon(Key.OptionIcon);
		Grid->Init(UnChooseBGImage,NSLOCTEXT("PackageUserWidget","Grid","Option"));
		Grid->SetIsOption(true);
		PackageHorizontalBox->AddChild(SizeBox);
		GridArray.Add(Grid);
		PackageInfoMap.Add(Grid,Key);
		UWidgetLayoutLibrary::SlotAsHorizontalBoxSlot(SizeBox)->SetPadding(FVector4d(10,0,0,0));
	}
	TMap<int32, int32 >ItemMap;
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			ItemMap = PlayerCharacter->GetPackageComponent()->GetItemMap();
		}
		if (ItemMap.Num() >= 25)
		{
			ItemWidget->SpawnGrids((ItemMap.Num() % 5 + 1) * 5);
		}
		else
		{
			ItemWidget->SpawnGrids(25);
		}
	}
	for (auto ItemKey : ItemMap)
	{
		ItemWidget->BindGrids(ItemKey.Key);
	}
}

void UPackageUserWidget::UpdateArmorPanel(int32 ID)
{
	if (!ArmorPanelWidget)
	{
		TSubclassOf<UArmorPanelWidget> ArmorClass = LoadClass<UArmorPanelWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_ArmorPanel.WBP_ArmorPanel_C'"));
		ArmorPanelWidget = CreateWidget<UArmorPanelWidget>(GetOwningPlayer(),ArmorClass);
	}
	if (ArmorPanelWidget)
	{
		ItemPanelWidget->SetVisibility(ESlateVisibility::Hidden);
		WeaponPanelWidget->SetVisibility(ESlateVisibility::Hidden);
		ArmorPanelWidget->SetVisibility(ESlateVisibility::Visible);
		ArmorPanelWidget->UpdateArmorPanel(ID);
	}
}

void UPackageUserWidget::UpdateUseItemPanel(int32 ID)
{
	if (!ItemPanelWidget)
	{
		TSubclassOf<UItemPanelWidget> ItemClass = LoadClass<UItemPanelWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_ItemPanel.WBP_ItemPanel_C'"));
		ItemPanelWidget = CreateWidget<UItemPanelWidget>(GetOwningPlayer(),ItemClass);
	}
	if (ItemPanelWidget)
	{
		ArmorPanelWidget->SetVisibility(ESlateVisibility::Hidden);
		WeaponPanelWidget->SetVisibility(ESlateVisibility::Hidden);
		ItemPanelWidget->SetVisibility(ESlateVisibility::Visible);
		ItemPanelWidget->UpdateItemPanel(ID);
	}
}

void UPackageUserWidget::UpdateWeaponPanel(int32 ID)
{
	if (!WeaponPanelWidget)
	{
		TSubclassOf<UWeaponPanelWidget> WeaponClass = LoadClass<UWeaponPanelWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_WeaponPanel.WBP_WeaponPanel_C'"));
		WeaponPanelWidget = CreateWidget<UWeaponPanelWidget>(GetOwningPlayer(),WeaponClass);
	}
	if (WeaponPanelWidget)
	{
		ArmorPanelWidget->SetVisibility(ESlateVisibility::Hidden);
		ItemPanelWidget->SetVisibility(ESlateVisibility::Hidden);
		WeaponPanelWidget->SetVisibility(ESlateVisibility::Visible);
		WeaponPanelWidget->UpdateWeaponPanel(ID);
	}
}

void UPackageUserWidget::NextGrid()
{
	
	if (NowGrid)
	{
		for (auto key : PackageInfoMap)
		{
			if (key.Key == NowGrid)
			{
				for (int32 i = 0 ; i < PackageOptions.Num() ; i++)
				{
					if(PackageOptions[i] == key.Value)
					{
						if (i == PackageOptions.Num() - 1)
						{
							return;
						}
						FPackageOption NowPackageOption = PackageOptions[i + 1];
						for (auto NewKey : PackageInfoMap)
						{
							if (NewKey.Value == NowPackageOption)
							{
								SetItems(NewKey.Key);
								return;
							}
						}
					}
				}
			}
		}
	}
}

void UPackageUserWidget::BeforeGrid()
{
	
	if (NowGrid)
	{
		for (auto key : PackageInfoMap)
		{
			if (key.Key == NowGrid)
			{
				if (key.Key == PackageInfoMap.begin().Key())
				{
					return;	
				}
				for (int32 i = 0 ; i < PackageOptions.Num() ; i++)
				{
					if(PackageOptions[i] == key.Value)
					{
						FPackageOption NowPackageOption = PackageOptions[i - 1];
						for (auto NewKey : PackageInfoMap)
						{
							if (NewKey.Value == NowPackageOption)
							{
								SetItems(NewKey.Key);
								return;
							}
						}
					}
				}
			}
		}
	}
}

void UPackageUserWidget::SetItems(UGridWidget* Grid)
{
	if (PackageInfoMap.IsEmpty())
	{
		return;
	}
	if (!PackageInfoMap.Contains(Grid))
	{
		return;
	}
	NowGrid = Grid;
	for (auto key : GridArray)
	{
		key->SetVisibility(ESlateVisibility::Hidden);
	}
	if (GridArray.Num() > 5)
	{
		for (int32 i = 0; i < GridArray.Num(); i++)
		{
			if (GridArray[i] == Grid)
			{
				if (i < 2)
				{
					GridArray[0]->SetVisibility(ESlateVisibility::Visible);
					GridArray[1]->SetVisibility(ESlateVisibility::Visible);
					GridArray[2]->SetVisibility(ESlateVisibility::Visible);
					GridArray[3]->SetVisibility(ESlateVisibility::Visible);
					GridArray[4]->SetVisibility(ESlateVisibility::Visible);
					break;
				}
				if (i > GridArray.Num() - 3)
				{
					GridArray[GridArray.Num() - 1]->SetVisibility(ESlateVisibility::Visible);
					GridArray[GridArray.Num() - 2]->SetVisibility(ESlateVisibility::Visible);
					GridArray[GridArray.Num() - 3]->SetVisibility(ESlateVisibility::Visible);
					GridArray[GridArray.Num() - 4]->SetVisibility(ESlateVisibility::Visible);
					GridArray[GridArray.Num() - 5]->SetVisibility(ESlateVisibility::Visible);
					break;
				}
				GridArray[i]->SetVisibility(ESlateVisibility::Visible);
				GridArray[i + 1]->SetVisibility(ESlateVisibility::Visible);
				GridArray[i + 2]->SetVisibility(ESlateVisibility::Visible);
				GridArray[i - 1]->SetVisibility(ESlateVisibility::Visible);
				GridArray[i - 2]->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
	TMap<int32, int32 >ItemMap;
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			ItemMap = PlayerCharacter->GetPackageComponent()->GetItemMap();
		}
		if (ItemMap.Num() >= 25)
		{
			ItemWidget->SpawnGrids((ItemMap.Num() % 5 + 1) * 5);
		}
		else
		{
			ItemWidget->SpawnGrids(25);
		}
	}
	for (auto ItemKey : ItemMap)
	{
		if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ItemKey.Key))
		{
			if (PackageInfoMap[Grid].bIsAll)
			{
				ItemType->SetText(NSLOCTEXT("PackageUserWidget","All","所有道具"));
			}
			else
			{
				switch (PackageInfoMap[Grid].ItemType)
				{
				case EItemType::Armor: ItemType->SetText(NSLOCTEXT("PackageUserWidget","Armor","防具"));break;
				case EItemType::Weapon: ItemType->SetText(NSLOCTEXT("PackageUserWidget","Weapon","武器"));break;
				case EItemType::Arrow: ItemType->SetText(NSLOCTEXT("PackageUserWidget","Arrow","箭矢"));break;
				case EItemType::Bolt: ItemType->SetText(NSLOCTEXT("PackageUserWidget","Bolt","弩箭"));break;
				case EItemType::Spell: ItemType->SetText(NSLOCTEXT("PackageUserWidget","Spell","法术"));break;
				case EItemType::Talisman: ItemType->SetText(NSLOCTEXT("PackageUserWidget","Talisman","护符"));break;
				case EItemType::BattleAsh: ItemType->SetText(NSLOCTEXT("PackageUserWidget","BattleAsh","战灰"));break;
				case EItemType::UseableItem:
					switch (PackageInfoMap[Grid].UseItemType)
					{
				case EUseItemType::Consumable: ItemType->SetText(NSLOCTEXT("PackageUserWidget","Consumable","消耗品"));break;
				case EUseItemType::NotConsumable: ItemType->SetText(NSLOCTEXT("PackageUserWidget","NotConsumable","非消耗品"));break;
				case EUseItemType::Key: ItemType->SetText(NSLOCTEXT("PackageUserWidget","Key","关键道具"));break;
						default:break;
					}
					break;
					default:break;
				}
			}
			if (PackageInfoMap[Grid].bIsAll)
			{
				ItemWidget->BindGrids(ItemKey.Key);
			}
			else if (PackageInfoMap[Grid].ItemType == EItemType::UseableItem)
			{
				FUseableItem* UseItem = reinterpret_cast<FUseableItem*>(ItemInfo);
				if (PackageInfoMap[Grid].UseItemType == UseItem->UseItemType)
				{
					ItemWidget->BindGrids(ItemKey.Key);
				}
			}
			else if (ItemInfo->ItemType == PackageInfoMap[Grid].ItemType)
			{
				ItemWidget->BindGrids(ItemKey.Key);
			}
		}
	}
	PackageHorizontalBox->SetRenderTranslation(FVector2D(PackageInfoMap[Grid].Translation * -1,0));
}

void UPackageUserWidget::UpdatePanel(int32 ID)
{
	if (ID == -1)
	{
		ArmorPanelWidget->UpdateArmorPanel(ID);
		ItemPanelWidget->UpdateItemPanel(ID);
		WeaponPanelWidget->UpdateWeaponPanel(ID);
		return;
	}
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		switch (ItemInfo->ItemType)
		{
		case EItemType::Armor:UpdateArmorPanel(ID);break;
		case EItemType::Talisman:
		case EItemType::Spell:
		case EItemType::BattleAsh:
		case EItemType::UseableItem:UpdateUseItemPanel(ID);break;
		case EItemType::Arrow:
		case EItemType::Bolt:
		case EItemType::Weapon:UpdateWeaponPanel(ID);break;
			default:break;
		}
	}
}

