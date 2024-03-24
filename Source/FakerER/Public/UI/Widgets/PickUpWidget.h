// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UPickUpWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UImage* ItemIcon;
	UPROPERTY(meta=(BindWidget))
	class UGridWidget* ItemGrid;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(meta=(BindWidget))
	UImage* QualityImage;

	UPROPERTY()
	class UTexture2D* Normal;
	UPROPERTY()
	class UTexture2D* Rare;
	UPROPERTY()
	class UTexture2D* Legendary;
	
public:
	void Init(int32 ID, int32 Num);
};
