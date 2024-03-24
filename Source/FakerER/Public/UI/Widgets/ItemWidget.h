// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UWrapBox* WrapBox;
	
	UPROPERTY()
	class AERHUD* HUD ;

public:
	void SpawnGrids(int32 ID);
	void BindGrids(int32 ID);
};

