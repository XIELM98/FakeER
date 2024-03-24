// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/ArmorPanelWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Subsystem/ERSubsystem.h"

void UArmorPanelWidget::InitArmorPanel()
{
	UMaterialInterface* Blank = LoadObject<UMaterialInterface>(this,TEXT("/Script/Engine.Material'/Game/FakeER/Materials/M_Null.M_Null'"));
	ArmorIcon->SetBrushFromMaterial(Blank);
	ArmorName->SetText(NSLOCTEXT("ArmorPanel","init","-"));
	Weight->SetText(NSLOCTEXT("ArmorPanel","init","-"));
	PhysicalDefend->SetText(NSLOCTEXT("ArmorPanel","init","-"));
	MagicDefend->SetText(NSLOCTEXT("ArmorPanel","init","-"));
	FireAttDefend->SetText(NSLOCTEXT("ArmorPanel","init","-"));
	LightingAttDefend->SetText(NSLOCTEXT("ArmorPanel","init","-"));
	BloodingDefend->SetText(NSLOCTEXT("ArmorPanel","init","-"));
	PoisonDefend->SetText(NSLOCTEXT("ArmorPanel","init","-"));
	DeathDefend->SetText(NSLOCTEXT("ArmorPanel","init","-"));
	ToughnessDefend->SetText(NSLOCTEXT("ArmorPanel","init","-"));
}

void UArmorPanelWidget::UpdateArmorPanel(int32 ID)
{
	if (ID == -1)
	{
		InitArmorPanel();
	}
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		FArmorInfo* ArmorInfo = reinterpret_cast<FArmorInfo*>(ItemInfo);
		ArmorIcon->SetBrushFromTexture(ArmorInfo->Icon);
		ArmorName->SetText(ArmorInfo->Name);
		Weight->SetText(FText::AsNumber(ArmorInfo->Weight));
		PhysicalDefend->SetText(FText::AsNumber(ArmorInfo->PhysicalDefend));
		MagicDefend->SetText(FText::AsNumber(ArmorInfo->MagicDefend));
		FireAttDefend->SetText(FText::AsNumber(ArmorInfo->FireDefend));
		LightingAttDefend->SetText(FText::AsNumber(ArmorInfo->LightingDefend));
		BloodingDefend->SetText(FText::AsNumber(ArmorInfo->BloodingDefend));
		PoisonDefend->SetText(FText::AsNumber(ArmorInfo->PoisonDefend));
		DeathDefend->SetText(FText::AsNumber(ArmorInfo->DeathDefend));
		ToughnessDefend->SetText(FText::AsNumber(ArmorInfo->ToughnessDefend));
	}
}
