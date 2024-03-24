// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PackageComponent.h"

#include "ERHUD.h"
#include "Actors/UseItemActor.h"
#include "Actors/WeaponActor.h"
#include "Characters/ERCharacterBase.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ERSubsystem.h"
#include "UI/EquipUserWidget.h"
#include "UI/MenuUserWidget.h"

// Sets default values for this component's properties
UPackageComponent::UPackageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPackageComponent::BeginPlay()
{
	Super::BeginPlay();

	OnEquipFromPackage.AddUObject(this,&UPackageComponent::OnEquipItem);
	OnUnEquipFromPackage.AddUObject(this,&UPackageComponent::OnUnEquipItem);
	OnUseItem.AddUObject(this,&UPackageComponent::ItemUsed);
	AllItemMap.Append(PreItemMap);
}




// Called every frame
void UPackageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPackageComponent::AddItemToPackage(int32 InID, int32 Num)
{
	if (AllItemMap.Contains(InID))
	{
		AllItemMap[InID] = AllItemMap[InID] + Num;
	}
	else
	{
		AllItemMap.Add(InID,Num);
	}
}

int32 UPackageComponent::GetItemNum(int32 ID)
{
	if (AllItemMap.Contains(ID))
	{
		return AllItemMap[ID];
	}
	else
	{
		return 0;
	}
}

void UPackageComponent::OnEquipItem(int32 ID)
{
	if (ID == -1)
	{
		return;
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->ChangeItemEquip(ID);
	if (ID >= USEITEMINDEX && ID < WEAPONINDEX)
	{
		UpdateItem();
	}
	else if (ID >= WEAPONINDEX && ID < ARMORNDEX)
	{
		UpdateRightWeapon();
		UpdateLeftWeapon();
	}
	else if (ID >= ARMORNDEX && ID < TALISMAXINDEX)
	{
		UpdateArmor(ID,true);
	}
}

void UPackageComponent::OnUnEquipItem(int32 ID)
{
	if (ID == -1)
	{
		return;
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->ChangeItemEquip(ID);
	if (ID >= USEITEMINDEX && ID < WEAPONINDEX)
	{
		UpdateItem();
	}
	else if (ID >= WEAPONINDEX && ID < ARMORNDEX)
	{
		UpdateRightWeapon();
		UpdateLeftWeapon();
	}
	else if (ID >= ARMORNDEX && ID < TALISMAXINDEX)
	{
		UpdateArmor(ID,false);
	}
	ClearItem();
}

void UPackageComponent::UpdateRightWeapon()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if (UEquipUserWidget* EquipUserWidget = HUD->GetMenuUserWidget()->GetEquipWidget())
		{
			if (EquipRightWeaponMap.Contains(1))
			{
				EquipRightWeaponMap.Remove(1);
			}
			EquipRightWeaponMap.Add(1,EquipUserWidget->RightWeapon1->GetBindItemID());

			if (EquipRightWeaponMap.Contains(2))
			{
				EquipRightWeaponMap.Remove(2);
			}
			EquipRightWeaponMap.Add(2,EquipUserWidget->RightWeapon2->GetBindItemID());
			
			if (EquipRightWeaponMap.Contains(3))
			{
				EquipRightWeaponMap.Remove(3);
			}
			EquipRightWeaponMap.Add(3,EquipUserWidget->RightWeapon3->GetBindItemID());
		}
	}
}

void UPackageComponent::UpdateLeftWeapon()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if (UEquipUserWidget* EquipUserWidget = HUD->GetMenuUserWidget()->GetEquipWidget())
		{

			if (EquipLeftWeaponMap.Contains(1))
			{
				EquipLeftWeaponMap.Remove(1);
			}
			EquipLeftWeaponMap.Add(1,EquipUserWidget->LeftWeapon1->GetBindItemID());

			if (EquipLeftWeaponMap.Contains(2))
			{
				EquipLeftWeaponMap.Remove(2);
			}
			EquipLeftWeaponMap.Add(2,EquipUserWidget->LeftWeapon2->GetBindItemID());

			if (EquipLeftWeaponMap.Contains(3))
			{
				EquipLeftWeaponMap.Remove(3);
			}
			EquipLeftWeaponMap.Add(3,EquipUserWidget->LeftWeapon3->GetBindItemID());
		}
	}
}

void UPackageComponent::UpdateItem()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if (UEquipUserWidget* EquipUserWidget = HUD->GetMenuUserWidget()->GetEquipWidget())
		{
			EquipItemMap.Empty();
			for (int32 i = 0; i < EquipUserWidget->Item1->GetChildrenCount(); i++)
			{
				if (UGridWidget* ItemGrid = Cast<UGridWidget>(EquipUserWidget->Item1->GetChildAt(i)))
				{
					if (EquipItemMap.Contains(i))
                    {
                        EquipItemMap.Remove(i);
                    }
                    EquipItemMap.Add(i,ItemGrid->GetBindItemID());
				}
			}
			for (int32 i = 0; i < EquipUserWidget->Item2->GetChildrenCount(); i++)
			{
				if (UGridWidget* ItemGrid = Cast<UGridWidget>(EquipUserWidget->Item2->GetChildAt(i)))
				{
					if (EquipItemMap.Contains(i +  5))
                    {
                        EquipItemMap.Remove(i + 5);
                    }
                    EquipItemMap.Add(i +  5,ItemGrid->GetBindItemID());
				}
			}
		}
	}
}

void UPackageComponent::UpdateArmor(int32 ID, bool IsEquip)
{
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		FArmorInfo* ArmorInfo = reinterpret_cast<FArmorInfo*>(ItemInfo);
		if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(GetOwner()))
		{
			if (!IsEquip)
			{
				CharacterBase->GetCharacterPanel()->MaxToughness -= ArmorInfo->ToughnessDefend;
				CharacterBase->GetCharacterPanel()->PhysicalDefend -= ArmorInfo->PhysicalDefend;
				CharacterBase->GetCharacterPanel()->FireDefend -= ArmorInfo->FireDefend;
				CharacterBase->GetCharacterPanel()->MagicDefend -= ArmorInfo->MagicDefend;
				CharacterBase->GetCharacterPanel()->LightingDefend -= ArmorInfo->LightingDefend;
				CharacterBase->GetCharacterPanel()->BloodingDefend -= ArmorInfo->BloodingDefend;
				CharacterBase->GetCharacterPanel()->PoisonDefend -= ArmorInfo->PoisonDefend;
				CharacterBase->GetCharacterPanel()->DeathDefend -= ArmorInfo->DeathDefend;
			}
			if (IsEquip)
			{
				CharacterBase->GetCharacterPanel()->MaxToughness += ArmorInfo->ToughnessDefend;
				CharacterBase->GetCharacterPanel()->PhysicalDefend += ArmorInfo->PhysicalDefend;
				CharacterBase->GetCharacterPanel()->FireDefend += ArmorInfo->FireDefend;
				CharacterBase->GetCharacterPanel()->MagicDefend += ArmorInfo->MagicDefend;
				CharacterBase->GetCharacterPanel()->LightingDefend += ArmorInfo->LightingDefend;
				CharacterBase->GetCharacterPanel()->BloodingDefend += ArmorInfo->BloodingDefend;
				CharacterBase->GetCharacterPanel()->PoisonDefend += ArmorInfo->PoisonDefend;
				CharacterBase->GetCharacterPanel()->DeathDefend += ArmorInfo->DeathDefend;
			}
		}
	}
}

void UPackageComponent::UpdateTalisman(int32 ID, bool IsEquip)
{
	
}

void UPackageComponent::UpdateCharacterPanel(int32 ID, bool IsEquip, bool IsRight)
{
	if (ID == -1)
	{
		return;
	}
	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(GetOwner()))
	{
		if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
		{
			if (IsRight)
			{
				if (IsEquip)
				{
					FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo);
					CharacterBase->GetCharacterPanel()->RightPhysicalAttack = CharacterBase->GetCharacterPanel()->RightPhysicalAttack + WeaponInfo->PhysicalAttack + WeaponInfo->AdditionPhysicalAttack;
					CharacterBase->GetCharacterPanel()->RightFireAttack = CharacterBase->GetCharacterPanel()->RightFireAttack + WeaponInfo->FireAttack + WeaponInfo->AdditionFireAttack;
					CharacterBase->GetCharacterPanel()->RightLightingAttack = CharacterBase->GetCharacterPanel()->RightLightingAttack + WeaponInfo->LightingAttack + WeaponInfo->AdditionLightingAttack;
					CharacterBase->GetCharacterPanel()->RightMagicAttack = CharacterBase->GetCharacterPanel()->RightMagicAttack + WeaponInfo->MagicAttack + WeaponInfo->AdditionMagicAttack;
				}
				else
				{
					CharacterBase->GetCharacterPanel()->RightPhysicalAttack = CharacterBase->GetCharacterAttribute()->Level;
					CharacterBase->GetCharacterPanel()->RightMagicAttack = 0;
					CharacterBase->GetCharacterPanel()->RightFireAttack = 0;
					CharacterBase->GetCharacterPanel()->RightLightingAttack = 0;				
				}				
			}
			else
			{
				if (IsEquip)
				{
					FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo);
					CharacterBase->GetCharacterPanel()->LeftPhysicalAttack = CharacterBase->GetCharacterPanel()->LeftPhysicalAttack + WeaponInfo->PhysicalAttack + WeaponInfo->AdditionPhysicalAttack;
					CharacterBase->GetCharacterPanel()->LeftFireAttack = CharacterBase->GetCharacterPanel()->LeftFireAttack + WeaponInfo->FireAttack + WeaponInfo->AdditionFireAttack;
					CharacterBase->GetCharacterPanel()->LeftLightingAttack = CharacterBase->GetCharacterPanel()->LeftLightingAttack + WeaponInfo->LightingAttack + WeaponInfo->AdditionLightingAttack;
					CharacterBase->GetCharacterPanel()->LeftMagicAttack = CharacterBase->GetCharacterPanel()->LeftMagicAttack + WeaponInfo->MagicAttack + WeaponInfo->AdditionMagicAttack;
				}
				else
				{
					CharacterBase->GetCharacterPanel()->LeftPhysicalAttack = CharacterBase->GetCharacterAttribute()->Level;
					CharacterBase->GetCharacterPanel()->LeftMagicAttack = 0;
					CharacterBase->GetCharacterPanel()->LeftFireAttack = 0;
					CharacterBase->GetCharacterPanel()->LeftLightingAttack = 0;				
				}	
			}
		}
	}
}

void UPackageComponent::EquipRightWeapon(int32 ID)
{
	if (ID == -1)
	{
		if (RightHoldWeapon)
		{
			RightHoldWeapon->Destroy();
		}
		RightHoldWeapon = nullptr;
		return;
	}
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		if (FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo))
		{
			if (WeaponInfo->WeaponClass)
			{
				if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(GetOwner()))
				{
					if (RightHoldWeapon)
					{
						UpdateCharacterPanel(RightHoldWeapon->GetID(),false,true);
						RightHoldWeapon->Destroy();
					}
					UpdateCharacterPanel(ID,true,true);
					AWeaponActor * WeaponActor = GetWorld()->SpawnActor<AWeaponActor>(WeaponInfo->WeaponClass);
					WeaponActor->SetupMasterAndID(CharacterBase,ID);
					WeaponActor->AttachToComponent(CharacterBase->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("RightWeapon"));
					RightHoldWeapon = WeaponActor;
				}
			}
		}
	}
}

void UPackageComponent::EquipLeftWeapon(int32 ID)
{
	if (ID == -1)
	{
		if (LeftHoldWeapon)
		{
			LeftHoldWeapon->Destroy();
		}
		LeftHoldWeapon = nullptr;
		return;
	}
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		if (FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo))
		{
			if (WeaponInfo->WeaponClass)
			{
				if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(GetOwner()))
				{
					if (LeftHoldWeapon)
					{
						UpdateCharacterPanel(LeftHoldWeapon->GetID(),false,false);
						LeftHoldWeapon->Destroy();
					}
					UpdateCharacterPanel(ID,true,false);
					AWeaponActor * WeaponActor = GetWorld()->SpawnActor<AWeaponActor>(WeaponInfo->WeaponClass);
					WeaponActor->SetupMasterAndID(CharacterBase,ID);
					WeaponActor->AttachToComponent(CharacterBase->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("LeftWeapon"));
					LeftHoldWeapon = WeaponActor;
				}
			}
		}
	}
}

void UPackageComponent::DeleteUseItem()
{
	if (UseItemActor)
	{
		UseItemActor->Destroy();
		UseItemActor = nullptr;
	}	
}

void UPackageComponent::ClearItem()
{
	for (auto key : AllItemMap)
	{
		if (key.Value == 0)
		{
			if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(key.Key))
			{
				if (FUseableItem* UseItem = reinterpret_cast<FUseableItem*>(ItemInfo))
				{
					if (UseItem->UseItemType == EUseItemType::Consumable)
					{
						AllItemMap.Remove(key.Key);
					}
				}
			}
		}
	}
}

void UPackageComponent::ItemUsed(int32 ID)
{
	if (AllItemMap.Contains(ID))
	{
		AllItemMap[ID]--;
	}
}
