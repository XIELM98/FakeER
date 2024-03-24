// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/ItemPanelWidget.h"

#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/Image.h"
#include "Components/PackageComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ERSubsystem.h"

void UItemPanelWidget::InitItemPanel()
{
	UMaterialInterface* Blank = LoadObject<UMaterialInterface>(this,TEXT("/Script/Engine.Material'/Game/FakeER/Materials/M_Null.M_Null'"));
	ItemIcon->SetBrushFromMaterial(Blank);
	ItemName->SetText(NSLOCTEXT("ItemPanel","init","-"));
	ItemType->SetText(NSLOCTEXT("ItemPanel","init","-"));
	ItemNum->SetText(NSLOCTEXT("ItemPanel","init","-"));
	CostMana->SetText(NSLOCTEXT("ItemPanel","init","-"));
	ItemEffect->SetText(NSLOCTEXT("ItemPanel","init",""));
	NeedPower->SetText(FText::AsNumber(0));
	NeedAgile->SetText(FText::AsNumber(0));
	NeedIntelligence->SetText(FText::AsNumber(0));
	NeedBelief->SetText(FText::AsNumber(0));
	NeedPower->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	NeedAgile->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	NeedIntelligence->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	NeedBelief->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	MemorySpaceText->SetVisibility(ESlateVisibility::Hidden);
	MemorySpace->SetVisibility(ESlateVisibility::Hidden);
}

void UItemPanelWidget::UpdateUseItem(int32 ID)
{
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		FUseableItem* UseItem = reinterpret_cast<FUseableItem*>(ItemInfo);
		ItemName->SetText(UseItem->Name);
		switch (UseItem->UseItemType)
		{
		case EUseItemType::Consumable:ItemType->SetText(NSLOCTEXT("ItemPanel","ItemType","消耗品"));break;
		case EUseItemType::NotConsumable:ItemType->SetText(NSLOCTEXT("ItemPanel","ItemType","非消耗品"));break;
		case EUseItemType::Key:ItemType->SetText(NSLOCTEXT("ItemPanel","ItemType","关键道具"));break;
		}
		if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
		{
			if (PlayerCharacter->GetPackageComponent())
			{
				ItemNum->SetText(FText::AsNumber(PlayerCharacter->GetPackageComponent()->GetItemNum(ID)));
			}
		}
		ItemIcon->SetBrushFromTexture(ItemInfo->Icon);
		CostMana->SetText(FText::AsNumber(UseItem->CostMana));
		ItemEffect->SetText(UseItem->ItemEffect);
	}
}

void UItemPanelWidget::UpdateSpell(int32 ID)
{
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		FSpellInfo* SpellInfo = reinterpret_cast<FSpellInfo*>(ItemInfo);
		ItemName->SetText(SpellInfo->Name);
		switch (SpellInfo->SpellType)
		{
		case ESpellType::Magic:ItemType->SetText(NSLOCTEXT("ItemPanel","ItemType","魔法"));break;
		case ESpellType::Miracle:ItemType->SetText(NSLOCTEXT("ItemPanel","ItemType","祷告"));break;
			default:break;
		}
		MemorySpaceText->SetVisibility(ESlateVisibility::Visible);
		MemorySpace->SetVisibility(ESlateVisibility::Visible);
		MemorySpace->SetText(FText::AsNumber(SpellInfo->CostMemorySpace));
		if (AERPlayerCharacter* Player = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
		{
			if (Player->GetCharacterAttribute()->Intelligence < SpellInfo->NeedIntelligence)
			{
				NeedIntelligence->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
			}
			if (Player->GetCharacterAttribute()->Belief < SpellInfo->NeedBelief)
			{
				NeedBelief->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
			}
			if (Player->GetPackageComponent())
			{
				ItemNum->SetText(FText::AsNumber(Player->GetPackageComponent()->GetItemNum(ID)));
			}
		}
		ItemIcon->SetBrushFromTexture(ItemInfo->Icon);
		NeedIntelligence->SetText(FText::AsNumber(SpellInfo->NeedIntelligence));
		NeedBelief->SetText(FText::AsNumber(SpellInfo->NeedBelief));
		CostMana->SetText(FText::AsNumber(SpellInfo->CostMana));
		ItemEffect->SetText(SpellInfo->SpellEffect);
	}
}

void UItemPanelWidget::UpdateBattleAsh(int32 ID)
{
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		FBattleAsh* BattleAsh = reinterpret_cast<FBattleAsh*>(ItemInfo);
		
	}
}

void UItemPanelWidget::UpdateTalisman(int32 ID)
{
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		FTalismanInfo* TalismanInfo = reinterpret_cast<FTalismanInfo*>(ItemInfo);
		
	}
}

void UItemPanelWidget::UpdateItemPanel(int32 ID)
{
	InitItemPanel();
	if (ID == -1)
	{
		return;
	}
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		switch (ItemInfo->ItemType)
		{
		case EItemType::UseableItem:
			UpdateUseItem(ID);
			break;
		case EItemType::Spell:
			UpdateSpell(ID);
			break;
		case EItemType::Talisman:
			UpdateTalisman(ID);
			break;
		case EItemType::BattleAsh:
			UpdateBattleAsh(ID);
			break;
		default:break;
		}

	}
}
