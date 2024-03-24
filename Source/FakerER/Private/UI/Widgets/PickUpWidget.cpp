// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PickUpWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Subsystem/ERSubsystem.h"
#include "UI/Widgets/GridWidget.h"

void UPickUpWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Normal = LoadObject<UTexture2D>(this,TEXT("/Script/Engine.Texture2D'/Game/FakeER/Textures/Icon/Main/PackageScroll.PackageScroll'"));
	Rare = LoadObject<UTexture2D>(this,TEXT("/Script/Engine.Texture2D'/Game/FakeER/Textures/Icon/Main/Rare.Rare'"));
	Legendary = LoadObject<UTexture2D>(this,TEXT("/Script/Engine.Texture2D'/Game/FakeER/Textures/Icon/Main/Legandary.Legandary'"));
}

void UPickUpWidget::Init(int32 ID,int32 Num)
{
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		ItemIcon->SetBrushFromTexture(ItemInfo->Icon);
		ItemGrid->Init(nullptr,NSLOCTEXT("PickUp","ItemGrid","PickUpItem"));
		ItemGrid->BindItem(ID,Num);
		ItemName->SetText(ItemInfo->Name);
		switch (ItemInfo->ItemQuality)
		{
		case EItemQuality::Normal:
			QualityImage->SetBrushFromTexture(Normal);
			break;
		case EItemQuality::Rare:
			QualityImage->SetBrushFromTexture(Rare);
			break;
		case EItemQuality::Legendary:
			QualityImage->SetBrushFromTexture(Legendary);
			break;
		}
	}
}
