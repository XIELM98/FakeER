// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/EquipmentWidget.h"

#include "Characters/ERCharacterBase.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/PackageComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ERSubsystem.h"
#include "UI/Widgets/GridWidget.h"

void UEquipmentWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitGrids();
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			PlayerCharacter->GetPackageComponent()->OnEquipFromPackage.AddUObject(this,&UEquipmentWidget::OnEquip);
			PlayerCharacter->GetPackageComponent()->OnUnEquipFromPackage.AddUObject(this,&UEquipmentWidget::OnUnEquip);
			
			PlayerCharacter->GetPackageComponent()->OnChangeItem.AddUObject(this,&UEquipmentWidget::ChangeItem);
			PlayerCharacter->GetPackageComponent()->OnChangeSpell.AddUObject(this,&UEquipmentWidget::ChangeSpell);
			PlayerCharacter->GetPackageComponent()->OnChangeLeftWeapon.AddUObject(this,&UEquipmentWidget::ChangeLeftWeapon);
			PlayerCharacter->GetPackageComponent()->OnChangeRightWeapon.AddUObject(this,&UEquipmentWidget::ChangeRightWeapon);
			PlayerCharacter->GetPackageComponent()->OnUnEquipLeftWeapon.AddUObject(this,&UEquipmentWidget::UnEquipLeftWeapon);
			PlayerCharacter->GetPackageComponent()->OnUnEquipRightWeapon.AddUObject(this,&UEquipmentWidget::UnEquipRightWeapon);
			PlayerCharacter->GetPackageComponent()->OnEquipLeftWeapon.AddUObject(this,&UEquipmentWidget::EquipLeftWeapon);
			PlayerCharacter->GetPackageComponent()->OnEquipRightWeapon.AddUObject(this,&UEquipmentWidget::EquipRightWeapon);
			
			PlayerCharacter->GetPackageComponent()->OnUseItem.AddUObject(this,&UEquipmentWidget::OnUseItem);
			
		}
	}
}



void UEquipmentWidget::BindGridItemAndNum(UGridWidget* Grid, int32 ID)
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			if (ID == -1)
			{
				Grid->BindItem(-1);
				Grid->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				Grid->BindItem(ID,PlayerCharacter->GetPackageComponent()->GetItemNum(ID));
				if (PlayerCharacter->GetPackageComponent()->GetItemNum(ID) == 0)
				{
					Grid->SetGridUnUsable();
				}
				else
				{
					Grid->SetGridUsable();
				}
				Grid->SetVisibility(ESlateVisibility::HitTestInvisible);
			}
		}
	}
}

int32 UEquipmentWidget::GetEquipItem()
{
	if (ItemArray.Num() > 0)
	{
		return ItemArray[0];
	}
	return -1;
}




void UEquipmentWidget::InitGrids()
{
	EquipmentBG = LoadObject<UTexture2D>(nullptr,TEXT("/Script/Engine.Texture2D'/Game/FakeER/Textures/Icon/Equip/EquipmenBG.EquipmenBG'"));
    if (EquipmentBG)
    {
    	Spell->Init(EquipmentBG,NSLOCTEXT("Equipment","Equip","Spell"));
    	Item->Init(EquipmentBG,NSLOCTEXT("Equipment","Equip","Item"));
    	RightWeapon->Init(EquipmentBG,NSLOCTEXT("Equipment","Equip","RightWeapon"));
    	LeftWeapon->Init(EquipmentBG,NSLOCTEXT("Equipment","Equip","LeftWeapon"));
    	NextSpell1->Init(EquipmentBG,NSLOCTEXT("Equipment","Equip","NextSpell1"));
    	NextSpell2->Init(EquipmentBG,NSLOCTEXT("Equipment","Equip","NextSpell2"));
    	NextItem1->Init(EquipmentBG,NSLOCTEXT("Equipment","Equip","NextItem1"));
    	NextItem2->Init(EquipmentBG,NSLOCTEXT("Equipment","Equip","NextItem2"));
    }
}

void UEquipmentWidget::ChangeSpell()
{
	
}

void UEquipmentWidget::ChangeItem()
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			if (ItemArray.Num() <= 1)
			{
				return;
			}
			if (ItemArray.Num() == 2)
			{
				int32 Temp = ItemArray[0];
				ItemArray.RemoveAt(0);
				ItemArray.Add(Temp);
				BindGridItemAndNum(Item,ItemArray[0]);
				BindGridItemAndNum(NextItem1,ItemArray[1]);
				BindGridItemAndNum(NextItem2,-1);
			}
			if (ItemArray.Num() >= 3)
			{
				int32 Temp = ItemArray[0];
				ItemArray.RemoveAt(0);
				ItemArray.Add(Temp);
				BindGridItemAndNum(Item,ItemArray[0]);
				BindGridItemAndNum(NextItem1,ItemArray[1]);
				BindGridItemAndNum(NextItem2,ItemArray[2]);
			}
			ItemName->SetText(GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ItemArray[0])->Name);
		}
	}
}

void UEquipmentWidget::ChangeLeftWeapon()
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			if (LeftWeaponIDArray.Num() <= 0)
			{
				return;
			}
			else
			{
				int32 TempID = LeftWeaponIDArray[0];
				LeftWeaponIDArray.RemoveAt(0);
				LeftWeaponIDArray.Add(TempID);
			}
		}
	}
}

void UEquipmentWidget::ChangeRightWeapon()
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			if (RightWeaponIDArray.Num() <= 0)
			{
				return;
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Next"))
				int32 TempID = RightWeaponIDArray[0];
				RightWeaponIDArray.RemoveAt(0);
				RightWeaponIDArray.Add(TempID);
			}
		}
	}
}

void UEquipmentWidget::UnEquipLeftWeapon()
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			LeftWeapon->SetGridUnUsable();
			PlayerCharacter->GetPackageComponent()->EquipLeftWeapon(-1);
		}
	}
}

void UEquipmentWidget::UnEquipRightWeapon()
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			RightWeapon->SetGridUnUsable();
			PlayerCharacter->GetPackageComponent()->EquipRightWeapon(-1);
		}
	}
}

void UEquipmentWidget::EquipLeftWeapon()
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			if (LeftWeaponIDArray.Num() <= 0)
			{
				LeftWeapon->BindItem(-1);
				LeftWeapon->SetGridUsable();
				PlayerCharacter->GetPackageComponent()->EquipLeftWeapon(-1);
			}
			else
			{
				LeftWeapon->BindItem(LeftWeaponIDArray[0]);
				LeftWeapon->SetGridUsable();
				PlayerCharacter->GetPackageComponent()->EquipLeftWeapon(LeftWeaponIDArray[0]);
			}
		}
	}
}

void UEquipmentWidget::EquipRightWeapon()
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			if (RightWeaponIDArray.Num() <= 0)
			{
				RightWeapon->BindItem(-1);
				RightWeapon->SetGridUsable();
				PlayerCharacter->GetPackageComponent()->EquipRightWeapon(-1);
			}
			else
			{
				RightWeapon->BindItem(RightWeaponIDArray[0]);
				RightWeapon->SetGridUsable();
				PlayerCharacter->GetPackageComponent()->EquipRightWeapon(RightWeaponIDArray[0]);
			}
		}
	}
}

void UEquipmentWidget::SetUpItemArray()
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			TMap<int32, int32> TempItemMap;
			for (auto key : PlayerCharacter->GetPackageComponent()->GetEquipItemMap())
			{
				if (key.Value != -1)
				{
					TempItemMap.Add(key.Key,key.Value);
				}
			}
			if (TempItemMap.Num() <= 0)
			{
				Item->BindItem(-1);
				BindGridItemAndNum(NextItem1,-1);
				BindGridItemAndNum(NextItem2,-1);
				ItemArray.Empty();
				return;
			}
			if (Item->GetBindItemID() == -1)
			{
				ItemArray.Empty();
				for (auto key : TempItemMap)
				{
					ItemArray.Add(key.Value);
					SetUpItems();
				}
			}
			else
			{
				ItemArray.Empty();
				for (auto key : TempItemMap)
				{
					if (Item->GetBindItemID() == key.Value)
					{
						ItemArray.Add(key.Value);
						for (auto  key1 : TempItemMap)
						{
							if (key1.Key > key.Key)
							{
								ItemArray.Add(key1.Value);
							}
						}
						for (auto key2 : TempItemMap)
						{
							if (key2.Key < key.Key)
							{
								ItemArray.Add(key2.Value);
							}
						}
						SetUpItems();
						return;
					}
				}
				for (auto key : TempItemMap)
				{
					ItemArray.Add(key.Value);
				}
				SetUpItems();
			}
		}
	}
}

void UEquipmentWidget::SetUpItems()
{
	if (ItemArray.Num() == 1)
	{
		BindGridItemAndNum(Item,ItemArray[0]);
		BindGridItemAndNum(NextItem1,-1);
		BindGridItemAndNum(NextItem2,-1);
	}
	if (ItemArray.Num() == 2)
	{
		BindGridItemAndNum(Item,ItemArray[0]);
		BindGridItemAndNum(NextItem1,ItemArray[1]);
		BindGridItemAndNum(NextItem2,-1);
	}
	if (ItemArray.Num() >= 3)
	{
		BindGridItemAndNum(Item,ItemArray[0]);
		BindGridItemAndNum(NextItem1,ItemArray[1]);
		BindGridItemAndNum(NextItem2,ItemArray[2]);
	}
}


void UEquipmentWidget::SetUpSpell()
{
	
}

void UEquipmentWidget::OnEquip(int32 ID)
{
	if (ID == -1)
	{
		return;
	}
	SetUpWeapon();
	SetUpItemArray();
}

void UEquipmentWidget::OnUnEquip(int32 ID)
{
	if (ID == -1)
	{
		return;
	}
	if (RightWeapon->GetBindItemID() != -1)
	{
		ChangeRightWeapon();
	}
	if (LeftWeapon->GetBindItemID() != -1)
	{
		ChangeLeftWeapon();
	}
	SetUpItemArray();
	
}

void UEquipmentWidget::OnUseItem(int32 ID)
{
	SetUpItems();
}

void UEquipmentWidget::SetUpWeapon()
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (PlayerCharacter->GetPackageComponent())
		{
			RightWeaponIDArray.Empty();
			LeftWeaponIDArray.Empty();
			for (auto key : PlayerCharacter->GetPackageComponent()->GetEquipRightWeaponMap())
			{
				if (key.Value != -1)
				{
					RightWeaponIDArray.Add(key.Value);
				}
			}
			if (RightWeaponIDArray.Num() == 1)
			{
				RightWeaponIDArray.Add(-1);
			}
			for (auto key : PlayerCharacter->GetPackageComponent()->GetEquipLeftWeaponMap())
			{
				if (key.Value != -1)
				{
					LeftWeaponIDArray.Add(key.Value);
				}
				if (LeftWeaponIDArray.Num() == 1)
				{
					LeftWeaponIDArray.Add(-1);
				}
			}
			if (RightWeapon->GetBindItemID() == -1 && RightWeaponIDArray.Num() >= 1 )
			{
				RightWeapon->BindItem(RightWeaponIDArray[0]);
				PlayerCharacter->GetPackageComponent()->EquipRightWeapon(RightWeaponIDArray[0]);
			}
			if (!PlayerCharacter->GetPackageComponent()->GetEquipRightWeaponMap().Contains(RightWeapon->GetBindItemID()))
			{
				RightWeapon->BindItem(-1);
				if (RightWeaponIDArray.Num() > 0)
				{
					RightWeapon->BindItem(RightWeaponIDArray[0]);
					PlayerCharacter->GetPackageComponent()->EquipRightWeapon(RightWeaponIDArray[0]);
				}
			}
			if (LeftWeapon->GetBindItemID() == -1 && LeftWeaponIDArray.Num() >= 1)
			{
				LeftWeapon->BindItem(LeftWeaponIDArray[0]);
				PlayerCharacter->GetPackageComponent()->EquipLeftWeapon(LeftWeaponIDArray[0]);
			}
			if (!PlayerCharacter->GetPackageComponent()->GetEquipLeftWeaponMap().Contains(LeftWeapon->GetBindItemID()))
			{
				LeftWeapon->BindItem(-1);
				if (LeftWeaponIDArray.Num() > 0)
				{
					LeftWeapon->BindItem(LeftWeaponIDArray[0]);
					PlayerCharacter->GetPackageComponent()->EquipLeftWeapon(LeftWeaponIDArray[0]);
				}
			}
		}
	}
}
