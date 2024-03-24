// Fill out your copyright notice in the Description page of Project Settings.


#include "ERHUD.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/MainUserWidget.h"
#include "UI/MenuUserWidget.h"
#include "UI/RestUserWidget.h"
#include "UI/Widgets/PickUpWidget.h"
#include "UI/Widgets/TipsWidget.h"

void AERHUD::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void AERHUD::BeginPlay()
{
	Super::BeginPlay();

	CurrentMenuPage = EMenuPage::Main;
	if (!MainUI)
	{
		TSubclassOf<UMainUserWidget> MainUIClass = LoadClass<UMainUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/WBP_MainUI.WBP_MainUI_C'"));
		MainUI = CreateWidget<UMainUserWidget>(GetOwningPlayerController(),MainUIClass);
	}
	if (MainUI && !MainUI->IsInViewport())
	{
		MainUI->AddToViewport();		
	}
}


void AERHUD::ToggleMenu()
{
	if (!MenuUserWidget)
	{
		TSubclassOf<UMenuUserWidget> MenuClass = LoadClass<UMenuUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/WBP_MenuUI.WBP_MenuUI_C'"));
		MenuUserWidget = CreateWidget<UMenuUserWidget>(GetOwningPlayerController(),MenuClass);
	}
	if (!MainUI)
	{
		TSubclassOf<UMainUserWidget>MainUIClass = LoadClass<UMainUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/WBP_MainUI.WBP_MainUI_C'"));
		MainUI = CreateWidget<UMainUserWidget>(GetOwningPlayerController(),MainUIClass);
	}
	if (MenuUserWidget)
	{
		if (!MenuUserWidget->IsInViewport())//开菜单
		{
			MenuUserWidget->AddToViewport();
			GetOwningPlayerController()->bShowMouseCursor = true;
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetOwningPlayerController());
			MainUI->RemoveFromParent();
			MainUI->AddToViewport();
			MainUI->OpenMenu();
			CurrentMenuPage = EMenuPage::Menu;
			return;
		}
		if (MenuUserWidget->IsInViewport())//关菜单
		{
			MenuUserWidget->RemoveFromParent();
			GetOwningPlayerController()->bShowMouseCursor = false;
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetOwningPlayerController());
			MainUI->ShowMainUI();
			CurrentMenuPage = EMenuPage::Main;
			return;
		}
	}
}

void AERHUD::HideMenu()
{
	if (MenuUserWidget && MenuUserWidget->IsInViewport())
	{
		MenuUserWidget->RemoveFromParent();
		MainUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AERHUD::ShowMenu()
{
	if (!MenuUserWidget)
	{
		TSubclassOf<UMenuUserWidget> MenuClass = LoadClass<UMenuUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/WBP_MenuUI.WBP_MenuUI_C'"));
		MenuUserWidget = CreateWidget<UMenuUserWidget>(GetOwningPlayerController(),MenuClass);
	}
	if (!MenuUserWidget->IsInViewport())
	{
		MenuUserWidget->AddToViewport();
		CurrentMenuPage = EMenuPage::Menu;
	}
	MainUI->RemoveFromParent();
	MainUI->AddToViewport();
	MainUI->SetVisibility(ESlateVisibility::HitTestInvisible);
	MainUI->OpenMenu();
}



void AERHUD::ToggleRestUI()
{
	if (!RestUserWidget)
	{
		TSubclassOf<URestUserWidget>RestClass = LoadClass<URestUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/WBP_RestUI.WBP_RestUI_C'"));
		RestUserWidget = CreateWidget<URestUserWidget>(GetOwningPlayerController(),RestClass);
	}
	if (RestUserWidget)
	{
		if (RestUserWidget->IsInViewport())
		{
			RestUserWidget->RemoveFromParent();
			GetOwningPlayerController()->bShowMouseCursor = false;
		}
		if (!RestUserWidget->IsInViewport())
		{
			RestUserWidget->AddToViewport();			
			GetOwningPlayerController()->bShowMouseCursor = true;
		}
	}
}

void AERHUD::HideTips()
{
	if (TipsWidget && TipsWidget->IsInViewport())
	{
		TipsWidget->RemoveFromParent();
		CurrentMenuPage = EMenuPage::Main;
	}
}

void AERHUD::ShowTips(FText ShowText)
{
	if (!TipsWidget)
	{
		TSubclassOf<UTipsWidget>TipsClass = LoadClass<UTipsWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_Tips.WBP_Tips_C'"));
		TipsWidget = CreateWidget<UTipsWidget>(GetOwningPlayerController(),TipsClass);
	}
	if (TipsWidget && !TipsWidget->IsInViewport())
	{
		TipsWidget->SetTips(KeyboardE,ShowText);
		if (!TipsWidget->IsInViewport())
		{
			TipsWidget->AddToViewport();			
		}
		//CurrentMenuPage = EMenuPage::Tips;
	}
}

void AERHUD::ShowPickUpUI(int32 ItemID, int32 ItemNum)
{
	if (!PickUpWidget)
	{
		TSubclassOf<UPickUpWidget> PickUpClass = LoadClass<UPickUpWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/Widgets/WBP_PickUp.WBP_PickUp_C'"));
		PickUpWidget = CreateWidget<UPickUpWidget>(GetOwningPlayerController(),PickUpClass);
	}
	if (PickUpWidget && !PickUpWidget->IsInViewport())
	{
		PickUpWidget->Init(ItemID, ItemNum);
		PickUpWidget->AddToViewport();
		HideTips();
		ShowTips(NSLOCTEXT("HUD","Check","确认"));
		CurrentMenuPage = EMenuPage::Tips;		
	}
}

void AERHUD::HidePickUpUI()
{
	if (PickUpWidget && PickUpWidget->IsInViewport())
	{
		PickUpWidget->RemoveFromParent();
		CurrentMenuPage = EMenuPage::Main;
	}
}



