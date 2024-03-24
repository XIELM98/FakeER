// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TipsWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UTipsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	class UImage* KeyIcon;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TipsText;

public:
	void SetTips(class UTexture2D* Icon, FText Text);
};
