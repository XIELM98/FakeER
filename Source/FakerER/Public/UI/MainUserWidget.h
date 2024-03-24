// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	class UPlayerInfoWidget* PlayerInfoWidget;
	UPROPERTY(meta=(BindWidget))
	class UEquipmentWidget* EquipmentWidget;

public:
	void OpenMenu();
	void ShowMainUI();
	UEquipmentWidget* GetEquipmentWidget() const {return EquipmentWidget;}
};
