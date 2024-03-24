// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ERSubsystem.h"

#include "Characters/Player/ERPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


void UERSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ItemDataTable = LoadObject<UDataTable>(this,TEXT("/Script/Engine.DataTable'/Game/FakeER/Data/Item/DT_Item.DT_Item'"));
	if (ItemDataTable)
	{
		TArray<FName> RowNames = ItemDataTable->GetRowNames();
		for (auto Key:RowNames)
		{
			FItemInfo* ItemInfo = reinterpret_cast<FItemInfo*>(ItemDataTable->GetRowMap()[Key]);
			if (ItemInfo)
			{
				int32 ID = 0;
				ID = FCString::Atoi(*Key.ToString());
				if (!ItemsMap.Contains(ID))
				{
					ItemsMap.Add(ID,ItemInfo);
				}
			}
		}
	}

	WeaponDataTable = LoadObject<UDataTable>(this,TEXT("/Script/Engine.DataTable'/Game/FakeER/Data/Item/DT_Weapon.DT_Weapon'"));
	if (WeaponDataTable)
	{
		TArray<FName> RowNames = WeaponDataTable->GetRowNames();
		for (auto Key:RowNames)
		{
			FWeaponInfo* ItemInfo = reinterpret_cast<FWeaponInfo*>(WeaponDataTable->GetRowMap()[Key]);
			if (ItemInfo)
			{
				int32 ID = 0;
				ID = FCString::Atoi(*Key.ToString()) + WEAPONINDEX;
				if (!ItemsMap.Contains(ID))
				{
					ItemsMap.Add(ID,ItemInfo);					
				}
			}
		}
		UpdateAdditionAttack();
	}

	UDataTable* ArmorTable = LoadObject<UDataTable>(this,TEXT("/Script/Engine.DataTable'/Game/FakeER/Data/Item/DT_Armor.DT_Armor'"));
	if (ArmorTable)
	{
		TArray<FName> RowNames = ArmorTable->GetRowNames();
		for (auto Key:RowNames)
		{
			FWeaponInfo* ItemInfo = reinterpret_cast<FWeaponInfo*>(ArmorTable->GetRowMap()[Key]);
			if (ItemInfo)
			{
				int32 ID = 0;
				ID = FCString::Atoi(*Key.ToString()) + ARMORNDEX;
				if (!ItemsMap.Contains(ID))
				{
					ItemsMap.Add(ID,ItemInfo);					
				}
			}
		}
	}
	
	BattleAshTable = LoadObject<UDataTable>(this,TEXT(""));
	if (BattleAshTable)
	{
		TArray<FName> RowNames = BattleAshTable->GetRowNames();
		for (auto Key:RowNames)
		{
			FBattleAsh* ItemInfo = reinterpret_cast<FBattleAsh*>(BattleAshTable->GetRowMap()[Key]);
			if (ItemInfo)
			{
				int32 ID = 0;
				ID = FCString::Atoi(*Key.ToString()) + BATTLEASHINDEX;
				if (ItemsMap.Contains(ID))
				{
					ItemsMap.Add(ID,ItemInfo);					
				}
			}
		}
	}

	Test();
}

void UERSubsystem::Test()
{
	UE_LOG(LogTemp, Log, TEXT("Subsys"))
	for (auto key : ItemsMap)
	{
		key.Value->bIsEquip = false;
	}
}

void UERSubsystem::UpdateAdditionAttack()
{
	for (auto Key : ItemsMap)
	{
		if (Key.Value->ItemType == EItemType::Weapon)
		{
			if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
			{
				if (FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(Key.Value))
				{
					if (PlayerCharacter->GetCharacterAttribute()->Power >= WeaponInfo->NeedPower && PlayerCharacter->GetCharacterAttribute()->Agile >= WeaponInfo->NeedAgile)
					{
						WeaponInfo->AdditionPhysicalAttack = WeaponInfo->AdditionPower * PlayerCharacter->GetCharacterAttribute()->Power * ADDITIONRATE + WeaponInfo->AdditionAgile * PlayerCharacter->GetCharacterAttribute()->Agile * ADDITIONRATE;
					}
					else
					{
						WeaponInfo->AdditionPhysicalAttack = WeaponInfo->AdditionPower * PlayerCharacter->GetCharacterAttribute()->Power * ADDITIONRATE + WeaponInfo->AdditionAgile * PlayerCharacter->GetCharacterAttribute()->Agile * ADDITIONRATE - WeaponInfo->PhysicalAttack;
					}
					if (PlayerCharacter->GetCharacterAttribute()->Intelligence >= WeaponInfo->NeedIntelligence)
					{
						WeaponInfo->AdditionMagicAttack = WeaponInfo->AdditionIntelligence * PlayerCharacter->GetCharacterAttribute()->Intelligence ;
					}
					else
					{
						WeaponInfo->AdditionMagicAttack = WeaponInfo->AdditionIntelligence * PlayerCharacter->GetCharacterAttribute()->Intelligence - WeaponInfo->MagicAttack;
					}
					if (PlayerCharacter->GetCharacterAttribute()->Belief >= WeaponInfo->NeedBelief)
					{
						WeaponInfo->AdditionLightingAttack = WeaponInfo->AdditionBelief * PlayerCharacter->GetCharacterAttribute()->Belief * ADDITIONRATE;
					}
					else
					{
						WeaponInfo->AdditionLightingAttack = WeaponInfo->AdditionBelief * PlayerCharacter->GetCharacterAttribute()->Belief * ADDITIONRATE - WeaponInfo->LightingAttack;
					}
					if (PlayerCharacter->GetCharacterAttribute()->Intelligence >= WeaponInfo->NeedIntelligence && PlayerCharacter->GetCharacterAttribute()->Belief >= WeaponInfo->NeedBelief)
					{
						WeaponInfo->AdditionFireAttack = WeaponInfo->AdditionIntelligence * PlayerCharacter->GetCharacterAttribute()->Intelligence * ADDITIONRATE + WeaponInfo->AdditionBelief * PlayerCharacter->GetCharacterAttribute()->Belief * ADDITIONRATE;
					}
					else
					{
						WeaponInfo->AdditionFireAttack = WeaponInfo->AdditionIntelligence * PlayerCharacter->GetCharacterAttribute()->Intelligence * ADDITIONRATE + WeaponInfo->AdditionBelief * PlayerCharacter->GetCharacterAttribute()->Belief * ADDITIONRATE - WeaponInfo->FireAttack;
					}
						
				}
			}
		}
	}
}

FItemInfo* UERSubsystem::GetItemInfo(int32 ID)
{
	if (ItemsMap.Contains(ID))
	{
		return ItemsMap[ID];
	}
	return nullptr;
}

void UERSubsystem::ChangeItemEquip(int32 ID)
{
	if (ItemsMap.Contains(ID))
	{
		FItemInfo* ItemInfo = GetItemInfo(ID);
		ItemInfo->bIsEquip = !ItemInfo->bIsEquip;
		ItemsMap.Remove(ID);
		ItemsMap.Add(ID,ItemInfo);
	}
}

