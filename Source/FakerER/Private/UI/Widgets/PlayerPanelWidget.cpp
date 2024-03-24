// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PlayerPanelWidget.h"

#include "ERHUD.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ERSubsystem.h"
#include "UI/EquipUserWidget.h"

void UPlayerPanelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitPlayerPanel();
}

void UPlayerPanelWidget::InitPlayerPanel()
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		FCharacterAttribute* CharacterAttribute = PlayerCharacter->GetCharacterAttribute();
		FCharacterPanel* CharacterPanel = PlayerCharacter->GetCharacterPanel();
		HaveRune->SetText(FText::AsNumber(PlayerCharacter->GetHaveRune()));
		Level->SetText(FText::AsNumber(CharacterAttribute->Level));
		Red->SetText(FText::AsNumber(CharacterAttribute->Red));
		Blue->SetText(FText::AsNumber(CharacterAttribute->Blue));
		Green->SetText(FText::AsNumber(CharacterAttribute->Green));
		Power->SetText(FText::AsNumber(CharacterAttribute->Power));		
		Agile->SetText(FText::AsNumber(CharacterAttribute->Agile));
		Intelligence->SetText(FText::AsNumber(CharacterAttribute->Intelligence));
		Belief->SetText(FText::AsNumber(CharacterAttribute->Belief));
		NowHP->SetText(FText::AsNumber(CharacterPanel->NowHP));
		MaxHP->SetText(FText::AsNumber(CharacterPanel->MaxHP));
		NowMana->SetText(FText::AsNumber(CharacterPanel->NowMana));
		MaxMana->SetText(FText::AsNumber(CharacterPanel->MaxMana));
		Endurance->SetText(FText::AsNumber(CharacterPanel->MaxEndurance));
		NowEquipWeight->SetText(FText::AsNumber(CharacterPanel->NowEquipWeight));
		MaxEquipWeight->SetText(FText::AsNumber(CharacterPanel->MaxEquipWeight));
		EquipmentLevel->SetText(GetEquipLevel(CharacterPanel->NowEquipWeight));
		Toughness->SetText(FText::AsNumber(CharacterPanel->MaxToughness));
		MemorySpace->SetText(FText::AsNumber(CharacterPanel->MemorySpace));
		NowEquipWeight->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		EquipmentLevel->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		Toughness->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		SetSpells();
	}
}

void UPlayerPanelWidget::SetSpells()
{
	
}

FText UPlayerPanelWidget::GetEquipLevel(int32 Weight)
{
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		FCharacterPanel* CharacterPanel = PlayerCharacter->GetCharacterPanel();
		float LevelIndex = Weight / CharacterPanel->MaxEquipWeight;
		if (LevelIndex <= 0.3f)
		{
			return NSLOCTEXT("PlayerPanel","EquipmentLevel","（轻）");
		}
		else if (LevelIndex <= 0.7f)
		{
			return NSLOCTEXT("PlayerPanel","EquipmentLevel","（中）");
		}
		else if (LevelIndex <= 1.0f)
		{
			return NSLOCTEXT("PlayerPanel","EquipmentLevel","（重）");
		}
		else
		{
			return NSLOCTEXT("PlayerPanel","EquipmentLevel","（超重）");
		}
	}
	return NSLOCTEXT("PlayerPanel","EquipmentLevel","-");
}

void UPlayerPanelWidget::UpdatePlayerPanel(int32 ID)
{
	InitPlayerPanel();
	if (ID == -1)
	{
		return;
	}
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
		{
			FCharacterPanel* CharacterPanel = PlayerCharacter->GetCharacterPanel();
			if (ItemInfo->ItemType == EItemType::Weapon)
			{
				FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo);
				float Weight = CharacterPanel->NowEquipWeight + WeaponInfo->Weight;
				NowEquipWeight->SetText(FText::AsNumber(Weight));
				EquipmentLevel->SetText(GetEquipLevel(Weight));
			}
			if (ItemInfo->ItemType == EItemType::Armor)
			{
				FArmorInfo* ArmorInfo = reinterpret_cast<FArmorInfo*>(ItemInfo);
				float Weight = CharacterPanel->NowEquipWeight + ArmorInfo->Weight;
				NowEquipWeight->SetText(FText::AsNumber(Weight));
				EquipmentLevel->SetText(GetEquipLevel(Weight));
                Toughness->SetText(FText::AsNumber(CharacterPanel->MaxToughness + ArmorInfo->ToughnessDefend));
			}			
		}
	}
}
