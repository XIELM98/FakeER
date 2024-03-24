// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipWeaponTipsWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UEquipWeaponTipsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void OnButtonClick();
	void SetBindID();
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UButton* CheckButton;
	int32 BindID;

public:
	void SetBindID(int32 NewID){BindID = NewID;}
};
