// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UPlayerInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HPBar;
	UPROPERTY(meta=(BindWidget))
	UProgressBar* MPBar;
	UPROPERTY(meta=(BindWidget))
	UProgressBar* EnduranceBar;
	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* Buffs;
	UPROPERTY(meta=(BindWidget))
	class UImage* TeamIcon;

public:
	void LevelUp();
};
