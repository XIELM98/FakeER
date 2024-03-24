// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUserWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "UI/Widgets/EquipmentWidget.h"
#include "UI/Widgets/PlayerInfoWidget.h"

void UMainUserWidget::OpenMenu()
{
	if (!PlayerInfoWidget)
	{
		TSubclassOf<UPlayerInfoWidget> PlayerInfoClass = LoadClass<UPlayerInfoWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_PlayerInfo.WBP_PlayerInfo_C'"));
		PlayerInfoWidget = CreateWidget<UPlayerInfoWidget>(this,PlayerInfoClass);
	}
	if (!EquipmentWidget)
	{
		TSubclassOf<UEquipmentWidget> EquipmentClass = LoadClass<UEquipmentWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/BP_Equipment.BP_Equipment_C'"));
		EquipmentWidget = CreateWidget<UEquipmentWidget>(this,EquipmentClass);
	}
	if (PlayerInfoWidget)
	{
		PlayerInfoWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	if (EquipmentWidget )
	{
		EquipmentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainUserWidget::ShowMainUI()
{
	if (!PlayerInfoWidget)
	{
		TSubclassOf<UPlayerInfoWidget> PlayerInfoClass = LoadClass<UPlayerInfoWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_PlayerInfo.WBP_PlayerInfo_C'"));
		PlayerInfoWidget = CreateWidget<UPlayerInfoWidget>(this,PlayerInfoClass);
	}
	if (!EquipmentWidget)
	{
		TSubclassOf<UEquipmentWidget> EquipmentClass = LoadClass<UEquipmentWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/BP_Equipment.BP_Equipment_C'"));
		EquipmentWidget = CreateWidget<UEquipmentWidget>(this,EquipmentClass);
	}
	if (PlayerInfoWidget )
	{
		PlayerInfoWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	if (EquipmentWidget )
	{
		EquipmentWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

