// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuUserWidget.h"

#include "ERHUD.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ConfigUserWidget.h"
#include "UI/EquipUserWidget.h"
#include "UI/PackageUserWidget.h"
#include "UI/StateUserWidget.h"



void UMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	EquipWidgetButton->OnClicked.AddDynamic(this,&UMenuUserWidget::OpenEquipWidget);
	PackageWidgetButton->OnClicked.AddDynamic(this,&UMenuUserWidget::OpenPackageWidget);
	StateWidgetButton->OnClicked.AddDynamic(this,&UMenuUserWidget::UMenuUserWidget::OpenStateWidget);
	ConfigWidgetButton->OnClicked.AddDynamic(this,&UMenuUserWidget::UMenuUserWidget::OpenConfigWidget);
}

void UMenuUserWidget::OpenEquipWidget()
{
	AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD());
	if (HUD)
	{
		HUD->HideMenu();
	}
	UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = true;

	if (!EquipWidget)
	{
		TSubclassOf<UEquipUserWidget>EquipClass = LoadClass<UEquipUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/WBP_EquipUI.WBP_EquipUI_C'"));
		EquipWidget = CreateWidget<UEquipUserWidget>(GetOwningPlayer(),EquipClass);
	}
	if (EquipWidget)
	{
		if (!EquipWidget->IsInViewport())
		{
			EquipWidget->AddToViewport();
			HUD->SetCurrentMenuPage(EMenuPage::Equip);
		}
	}
}

void UMenuUserWidget::OpenPackageWidget()
{
	AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD());
	if (HUD)
	{
		HUD->HideMenu();
	}
	UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = true;

	if (!PackageWidget)
	{
		TSubclassOf<UPackageUserWidget>PackageClass = LoadClass<UPackageUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/WBP_PackageUI.WBP_PackageUI_C'"));
		PackageWidget = CreateWidget<UPackageUserWidget>(GetOwningPlayer(),PackageClass);
	}
	if (PackageWidget)
	{
		if (!PackageWidget->IsInViewport())
		{
			PackageWidget->AddToViewport();
			HUD->SetCurrentMenuPage(EMenuPage::Package);
		}
	}
}

void UMenuUserWidget::OpenStateWidget()
{
	AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD());
	if (HUD)
	{
		HUD->HideMenu();
	}
	UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = true;

	if (!StateWidget)
	{
		TSubclassOf<UStateUserWidget>EquipClass = LoadClass<UStateUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/WBP_StateUI.WBP_StateUI_C'"));
		StateWidget = CreateWidget<UStateUserWidget>(GetOwningPlayer(),EquipClass);
	}
	if (StateWidget)
	{
		if (!StateWidget->IsInViewport())
		{
			StateWidget->AddToViewport();
			HUD->SetCurrentMenuPage(EMenuPage::State);
		}
	}
}

void UMenuUserWidget::OpenConfigWidget()
{
	AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD());
	if (HUD)
	{
		HUD->HideMenu();
	}
	UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = true;
	
	if (!ConfigWidget)
	{
		TSubclassOf<UConfigUserWidget>EquipClass = LoadClass<UConfigUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FakeER/UI/WBP_ConfigUI.WBP_ConfigUI_C'"));
		ConfigWidget = CreateWidget<UConfigUserWidget>(GetOwningPlayer(),EquipClass);
	}
	if (ConfigWidget)
	{
		if (!ConfigWidget->IsInViewport())
		{
			ConfigWidget->AddToViewport();
			HUD->SetCurrentMenuPage(EMenuPage::Config);
		}
	}
}
