// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EquipUserWidget.h"

#include "ERHUD.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/HorizontalBox.h"
#include "UI/Widgets/GridWidget.h"
#include "Components/PackageComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ERSubsystem.h"
#include "UI/Widgets/ArmorPanelWidget.h"
#include "UI/Widgets/ItemPanelWidget.h"
#include "UI/Widgets/ItemWidget.h"
#include "UI/Widgets/PlayerPanelWidget.h"
#include "UI/Widgets/WeaponPanelWidget.h"


void UEquipUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD());
    CreateGrids();
	ItemWidget->SetVisibility(ESlateVisibility::Hidden);

}



void UEquipUserWidget::CreateGrids()
{
	TSubclassOf<UGridWidget> GridClass = LoadClass<UGridWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_Grid.WBP_Grid_C'"));
	if (GridClass)
	{
		CreateWeapons();
		CreateOthers();		
	}
}

void UEquipUserWidget::CreateWeapons()
{
	RightWeapon1->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","RightWeapon","右手武器1"),HUD->WeaponImage);
	RightWeapon2->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","RightWeapon","右手武器2"),HUD->WeaponImage);
	RightWeapon3->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","RightWeapon","右手武器3"),HUD->WeaponImage);
	Arrow1->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","RightWeapon","弓箭1"),HUD->ArrowImage);
	Arrow2->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","RightWeapon","弓箭2"),HUD->ArrowImage);
	LeftWeapon1->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","LeftWeapon","左手武器1"),HUD->ShieldImage);
    LeftWeapon2->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","LeftWeapon","左手武器2"),HUD->ShieldImage);
    LeftWeapon3->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","LeftWeapon","左手武器3"),HUD->ShieldImage);
    Bolt1->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","LeftWeapon","弩箭1"),HUD->BoltImage);
    Bolt2->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","LeftWeapon","弩箭2"),HUD->BoltImage);

	AllGrids.Add(RightWeapon1);
	AllGrids.Add(RightWeapon2);
	AllGrids.Add(RightWeapon3);
	AllGrids.Add(LeftWeapon1);
	AllGrids.Add(LeftWeapon2);
	AllGrids.Add(LeftWeapon3);
	AllGrids.Add(Arrow1);
	AllGrids.Add(Arrow2);
	AllGrids.Add(Bolt1);
	AllGrids.Add(Bolt2);
	
}


void UEquipUserWidget::CreateOthers()
{
	TSubclassOf<UGridWidget> GridClass = LoadClass<UGridWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_Grid.WBP_Grid_C'"));
	UGridWidget* Grid1 = CreateWidget<UGridWidget>(this,GridClass);
	Grid1->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","Armor","头盔"),HUD->HelmetImage);
	Armor->AddChild(Grid1);
	UGridWidget* Grid2 = CreateWidget<UGridWidget>(this,GridClass);
	Grid2->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","Armor","盔甲"),HUD->BodyImage);
	Armor->AddChild(Grid2);
	UGridWidget* Grid3 = CreateWidget<UGridWidget>(this,GridClass);
	Grid3->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","Armor","手甲"),HUD->HandImage);
	Armor->AddChild(Grid3);
	UGridWidget* Grid4 = CreateWidget<UGridWidget>(this,GridClass);
	Grid4->Init(HUD->EquipBGImage,NSLOCTEXT("Equip","Armor","腿甲"),HUD->FootImage);
	Armor->AddChild(Grid4);
	AllGrids.Add(Grid1);
	AllGrids.Add(Grid2);
	AllGrids.Add(Grid3);
	AllGrids.Add(Grid4);
	for (int i = 0; i < 4 ; i++)
	{
		UGridWidget* TalismanGrid = CreateWidget<UGridWidget>(this,GridClass);
		TalismanGrid->Init(HUD->EquipBGImage,FText::Format(NSLOCTEXT("Equip","Talisman","护符 {0} "), i + 1 ),HUD->TalismanImage);
		Talisman->AddChild(TalismanGrid);
		AllGrids.Add(TalismanGrid);
	}
	for (int i = 0; i < 5 ; i++)
	{
		UGridWidget* ItemGrid = CreateWidget<UGridWidget>(this,GridClass);
		ItemGrid->Init(HUD->EquipBGImage,FText::Format(NSLOCTEXT("Equip","Item","道具 {0} "), i + 1),HUD->ItemImage);
		Item1->AddChild(ItemGrid);
		AllGrids.Add(ItemGrid);
	}
	for (int i = 0; i < 5 ; i++)
	{
		UGridWidget* ItemGrid = CreateWidget<UGridWidget>(this,GridClass);
		ItemGrid->Init(HUD->EquipBGImage,FText::Format(NSLOCTEXT("Equip","Item","道具 {0} "), i + 6),HUD->ItemImage);
		Item2->AddChild(ItemGrid);
		AllGrids.Add(ItemGrid);
	}	
}

void UEquipUserWidget::UpdateWeaponPanel(int32 ID)
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

void UEquipUserWidget::UpdateUseItemPanel(int32 ID)
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

void UEquipUserWidget::UpdateArmorPanel(int32 ID)
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

void UEquipUserWidget::SetGridInfo(FText InGridPos, FText InItemName)
{
	GridPos->SetText(InGridPos);
	ItemName->SetText(InItemName);
}

void UEquipUserWidget::ChooseItem(EItemType InItemType,EArmorType InArmorType)
{	
	TMap<int32, int32 >ItemMap;
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			ItemMap = PlayerCharacter->GetPackageComponent()->GetItemMap();
		}
		if (ItemMap.Num() >= 30)
		{
			ItemWidget->SpawnGrids((ItemMap.Num() % 5 + 1) * 5);
		}
		else
		{
			ItemWidget->SpawnGrids(30);
		}
		if (ItemWidget->GetVisibility() != ESlateVisibility::Visible)
		{
			ItemWidget->SetVisibility(ESlateVisibility::Visible);
			HUD->SetCurrentMenuPage(EMenuPage::ChooseItem);
		}
		
		
		for (auto Item : ItemMap)
		{
			if (FItemInfo* ItemInfo = (GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(Item.Key)))
			{
				if (ItemInfo->ItemType == InItemType)
				{
					if (InItemType == EItemType::Armor)
					{
						if(FArmorInfo* ArmorInfo = reinterpret_cast<FArmorInfo*>(ItemInfo))
						{
							if (ArmorInfo->ArmorType == InArmorType)
							{
								ItemWidget->BindGrids(Item.Key);
							}
						}
					}
					else if (InItemType == EItemType::UseableItem)
					{
						if(FUseableItem* UseItem = reinterpret_cast<FUseableItem*>(ItemInfo))
						{
							if (UseItem->UseItemType != EUseItemType::Key)
							{
								ItemWidget->BindGrids(Item.Key);
							}
						}
					}
					else
					{
						ItemWidget->BindGrids(Item.Key);
					}
				}
			}
		}
	}
}

void UEquipUserWidget::BindChooseGrid(int32 ID)
{
	AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (ChooseGrid && PlayerCharacter)
	{
		//卸载装备
		if (ID == -1 && ChooseGrid->GetBindItemID() != -1)
		{
			int32 TempID = ChooseGrid->GetBindItemID();
			ChooseGrid->BindItem(-1);
			if (PlayerCharacter->GetCameraComponent() && PlayerCharacter->GetPackageComponent()->OnUnEquipFromPackage.IsBound())
			{
				PlayerCharacter->GetPackageComponent()->OnUnEquipFromPackage.Broadcast(TempID);
			}
		}
		else if(ID != -1)
		{
			if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
			{
				if (ItemInfo->bIsEquip)
				{
					for (auto key:AllGrids)
					{
						if (key->GetBindItemID() == ID)
						{
							//互换装备格子
							if (ID == ChooseGrid->GetBindItemID())
							{
								CloseItemWidget();
								return;
							}
							key->BindItem(ChooseGrid->GetBindItemID());
							ChooseGrid->BindItem(ID);
							if (PlayerCharacter->GetCameraComponent() && PlayerCharacter->GetPackageComponent()->OnUnEquipFromPackage.IsBound())
							{
								PlayerCharacter->GetPackageComponent()->OnUnEquipFromPackage.Broadcast(key->GetBindItemID());
								PlayerCharacter->GetPackageComponent()->OnUnEquipFromPackage.Broadcast(ID);
							}
							if (PlayerCharacter->GetCameraComponent() && PlayerCharacter->GetPackageComponent()->OnEquipFromPackage.IsBound())
							{
								PlayerCharacter->GetPackageComponent()->OnEquipFromPackage.Broadcast(key->GetBindItemID());
								PlayerCharacter->GetPackageComponent()->OnEquipFromPackage.Broadcast(ID);
							}
							break;
						}
					}
				}
				
				else
				{
					if (ChooseGrid->GetBindItemID() != -1)
					{
						if (ID == ChooseGrid->GetBindItemID())
						{
							CloseItemWidget();
							return;
						}
						ChooseGrid->BindItem(ID);
						if (PlayerCharacter->GetCameraComponent() && PlayerCharacter->GetPackageComponent()->OnUnEquipFromPackage.IsBound())
						{
							PlayerCharacter->GetPackageComponent()->OnUnEquipFromPackage.Broadcast(ChooseGrid->GetBindItemID());
						}
						if (PlayerCharacter->GetCameraComponent() && PlayerCharacter->GetPackageComponent()->OnEquipFromPackage.IsBound())
						{
							PlayerCharacter->GetPackageComponent()->OnEquipFromPackage.Broadcast(ID);
						}
					}
					if (ChooseGrid->GetBindItemID() == -1)
					{
						ChooseGrid->BindItem(ID);
						if (PlayerCharacter->GetCameraComponent() && PlayerCharacter->GetPackageComponent()->OnEquipFromPackage.IsBound())
						{
							PlayerCharacter->GetPackageComponent()->OnEquipFromPackage.Broadcast(ID);
						}
					}
				}
			}
		}
		CloseItemWidget();
	}
}

void UEquipUserWidget::CloseItemWidget()
{
	if (ItemWidget)
	{
		ItemWidget->SetVisibility(ESlateVisibility::Hidden);
		HUD->SetCurrentMenuPage(EMenuPage::Equip);
		if (ChooseGrid)
		{
			ChooseGrid = nullptr;
		}
	}
}

void UEquipUserWidget::SetItemName(FText InItemName)
{
	ItemName->SetText(InItemName);
}

void UEquipUserWidget::UpdatePlayerPanelWidget(int32 ID)
{
	if (!PlayerPanelWidget)
	{
		TSubclassOf<UPlayerPanelWidget> PlayerPanelClass = LoadClass<UPlayerPanelWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_PlayerPanel.WBP_PlayerPanel_C'"));
		PlayerPanelWidget = CreateWidget<UPlayerPanelWidget>(GetOwningPlayer(),PlayerPanelClass);
	}
	if (PlayerPanelWidget)
	{
		PlayerPanelWidget->UpdatePlayerPanel(ID);
	}
}

void UEquipUserWidget::UpdatePanelWidget(int32 ID)
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
