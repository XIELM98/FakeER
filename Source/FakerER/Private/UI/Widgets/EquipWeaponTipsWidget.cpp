// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/EquipWeaponTipsWidget.h"

#include "ERHUD.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/EquipUserWidget.h"
#include "UI/MenuUserWidget.h"

void UEquipWeaponTipsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CheckButton->OnClicked.AddDynamic(this,&UEquipWeaponTipsWidget::OnButtonClick);
}

void UEquipWeaponTipsWidget::OnButtonClick()
{
	SetBindID();
	RemoveFromParent();
}

void UEquipWeaponTipsWidget::SetBindID()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if(UEquipUserWidget* EquipUserWidget = HUD->GetMenuUserWidget()->GetEquipWidget())
		{
			EquipUserWidget->BindChooseGrid(BindID);
		}
	}
}
