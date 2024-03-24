// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/ItemWidget.h"

#include "ERHUD.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/WrapBox.h"
#include "Components/WrapBoxSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ERSubsystem.h"
#include "UI/Widgets/GridWidget.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD());
	//SpawnGrids(10);
}

void UItemWidget::SpawnGrids(int32 Num)
{
	if (WrapBox->HasAnyChildren())
	{
		WrapBox->ClearChildren();		
	}
	for (int32 i = 0 ; i < Num ; i++)
    {
		TSubclassOf<UGridWidget> GridClass = LoadClass<UGridWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_Grid.WBP_Grid_C'"));
		UGridWidget* GridWidget = CreateWidget<UGridWidget>(GetOwningPlayer(),GridClass);
		GridWidget->Init(HUD->PackageBGImage,NSLOCTEXT("ItemWidget","Item","ChooseItem"));
		WrapBox->AddChildToWrapBox(GridWidget);
		UWidgetLayoutLibrary::SlotAsWrapBoxSlot(GridWidget)->SetPadding(FMargin(FVector4d(2,2,2,2)));
    }
}

void UItemWidget::BindGrids(int32 ID)
{
	if (WrapBox->HasAnyChildren())
	{
        for (int32 i = 0; i < WrapBox->GetChildrenCount(); i++)
        {
	        UGridWidget* GridWidget = Cast<UGridWidget>(WrapBox->GetChildAt(i));
	        if (GridWidget->GetBindItemID() == -1)
	        {
		        if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
		        {
			        if (ItemInfo->bIsEquip)
			        {
			        	GridWidget->Init(HUD->WeaponImage,NSLOCTEXT("ItemWidget","Item","ChooseItem"));
			        }
		        }
		        GridWidget->BindItem(ID);
	        	return;
	        }
        }
	}
}
