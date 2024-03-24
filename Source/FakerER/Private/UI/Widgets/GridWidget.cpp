// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/GridWidget.h"

#include "ERHUD.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"
#include "UI/EquipUserWidget.h"
#include "UI/MenuUserWidget.h"
#include "Subsystem/ERSubsystem.h"
#include "UI/PackageUserWidget.h"
#include "UI/Widgets/EquipWeaponTipsWidget.h"


void UGridWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BindItemID = -1;
	bIsOption = false;
	GridButton->OnHovered.AddDynamic(this,&UGridWidget::OnGridHovered);
	GridButton->OnClicked.AddDynamic(this,&UGridWidget::OnGridClicked);
}

void UGridWidget::OnGridHovered()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		EMenuPage MenuPage = HUD->GetCurrentMenuPage();
		switch (MenuPage)
		{
		case EMenuPage::ChooseItem:ChooseHover();
			break;
		case EMenuPage::Equip:EquipHover();
			break;
		case EMenuPage::Package:PackageHover();
			break;
			default:break;
		}
	}
}

void UGridWidget::OnGridClicked()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		EMenuPage MenuPage = HUD->GetCurrentMenuPage();
		switch (MenuPage)
		{
		case EMenuPage::Equip:EquipClick();
			break;
		case EMenuPage::ChooseItem:ChooseClick();
			break;
		case EMenuPage::Package:PackageClick();
			break;
		default:break;
		}
	}
	//	UE_LOG(LogTemp, Log, TEXT("BindName %s"),*GridName.ToString())
}

void UGridWidget::EquipHover()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if(UEquipUserWidget* EquipUserWidget = HUD->GetMenuUserWidget()->GetEquipWidget())
		{
			if (EquipUserWidget)
            {
            	if (BindItemID != -1)
            	{
            		EquipUserWidget->SetGridInfo(GridName,GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(BindItemID)->Name);
            	}
            	else
            	{
            		EquipUserWidget->SetGridInfo(GridName,NSLOCTEXT("Equip","Grid","空"));
            	}
				EquipUserWidget->UpdatePanelWidget(BindItemID);
            }
		}
	}
}

void UGridWidget::ChooseHover()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if(UEquipUserWidget* EquipUserWidget = HUD->GetMenuUserWidget()->GetEquipWidget())
		{
			if (EquipUserWidget)
			{
				EquipUserWidget->UpdatePanelWidget(BindItemID);
				EquipUserWidget->UpdatePlayerPanelWidget(BindItemID);
				if (BindItemID != -1)
				{
					EquipUserWidget->SetItemName(GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(BindItemID)->Name);
				}
				else
				{
					EquipUserWidget->SetItemName(NSLOCTEXT("Equip","Grid","空"));
				}
			}
		}
	}
}

void UGridWidget::PackageHover()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		UPackageUserWidget* PackageUserWidget = HUD->GetMenuUserWidget()->GetPackageWidget();
		if (bIsOption)
		{
			return;
		}
		else
		{
			PackageUserWidget->UpdatePanel(BindItemID);
		}
	}
}

void UGridWidget::EquipClick()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if(UEquipUserWidget* EquipUserWidget = HUD->GetMenuUserWidget()->GetEquipWidget())
		{
			if (EquipUserWidget)
        	{
	            FString StringName = GridName.ToString();
				EquipUserWidget->SetChooseGrid(this);
        		if (StringName.Contains(TEXT("武器")))
        		{
        			EquipUserWidget->ChooseItem(EItemType::Weapon);
        		}
        		if (StringName.Contains(TEXT("弓箭")))
        		{
        			EquipUserWidget->ChooseItem(EItemType::Arrow);
        		}
        		if (StringName.Contains(TEXT("弩箭")))
        		{
        			EquipUserWidget->ChooseItem(EItemType::Bolt);
        		}
				if (StringName.Contains(TEXT("头盔")))
        		{
        			EquipUserWidget->ChooseItem(EItemType::Armor,EArmorType::Helmet);
        		}
				if (StringName.Contains(TEXT("盔甲")))
        		{
        			EquipUserWidget->ChooseItem(EItemType::Armor,EArmorType::Body);
        		}
				if (StringName.Contains(TEXT("手甲")))
        		{
        			EquipUserWidget->ChooseItem(EItemType::Armor,EArmorType::Hand);
        		}
				if (StringName.Contains(TEXT("腿甲")))
        		{
        			EquipUserWidget->ChooseItem(EItemType::Armor,EArmorType::Foot);
        		}
				if (StringName.Contains(TEXT("护符")))
        		{
        			EquipUserWidget->ChooseItem(EItemType::Talisman);
        		}
				if (StringName.Contains(TEXT("道具")))
        		{
        			EquipUserWidget->ChooseItem(EItemType::UseableItem);
        		}
        	}
		}
	}
}

void UGridWidget::ChooseClick()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if(UEquipUserWidget* EquipUserWidget = HUD->GetMenuUserWidget()->GetEquipWidget())
		{
			if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
			{
				if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(BindItemID))
				{
					if (ItemInfo->ItemType == EItemType::Weapon)
					{
						FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo);
						if (PlayerCharacter->GetCharacterAttribute()->Power >= WeaponInfo->NeedPower && PlayerCharacter->GetCharacterAttribute()->Agile >= WeaponInfo->NeedAgile
							&& PlayerCharacter->GetCharacterAttribute()->Intelligence >= WeaponInfo->NeedIntelligence && PlayerCharacter->GetCharacterAttribute()->Belief >= WeaponInfo->NeedBelief)
						{
							
						}
						else
						{
							TSubclassOf<UEquipWeaponTipsWidget>EquipTipsClass = LoadClass<UEquipWeaponTipsWidget>(this,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_EquipWeaponTip.WBP_EquipWeaponTip_C'"));
							UEquipWeaponTipsWidget* EquipWeaponTipsWidget = CreateWidget<UEquipWeaponTipsWidget>(GetOwningPlayer(),EquipTipsClass);
							EquipWeaponTipsWidget->AddToViewport();
							EquipWeaponTipsWidget->SetBindID(BindItemID);
							return;
						}
					}
				}
			}
			EquipUserWidget->BindChooseGrid(BindItemID);
		}
	}

}

void UGridWidget::PackageClick()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		UPackageUserWidget* PackageUserWidget = HUD->GetMenuUserWidget()->GetPackageWidget();
		if (bIsOption)
		{
			PackageUserWidget->SetItems(this);	
		}
		else
		{
			
		}
	}
}


void UGridWidget::Init(UTexture2D* InBackgroundImage, FText InGridName, UTexture2D* InBackGroundIcon)
{
	
	if (InBackgroundImage)
	{
		BackGroundImage->SetBrushFromTexture(InBackgroundImage);
	}
	if (InBackGroundIcon)
	{
		BackGroundIcon->SetBrushFromTexture(InBackGroundIcon);
	}
	GridName = InGridName;
}

void UGridWidget::BindItem(int32 ID, int32 Num)
{
	if (ID == -1)
	{
		BindItemID = ID;
		UMaterialInterface* MaterialInterface = LoadObject<UMaterialInterface>(nullptr,TEXT("/Script/Engine.Material'/Game/FakeER/Materials/M_Null.M_Null'"));
		Icon->SetBrushFromMaterial(MaterialInterface);
	}
	if (Num <= -1)
	{
		ItemNum->SetVisibility(ESlateVisibility::Hidden);		
	}
	else
	{
		ItemNum->SetVisibility(ESlateVisibility::Visible);
		ItemNum->SetText(FText::AsNumber(Num));
	}
	if (FItemInfo* TempItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
    {
        BindItemID = ID;
        Icon->SetBrushFromTexture(TempItemInfo->Icon);
    }
}



