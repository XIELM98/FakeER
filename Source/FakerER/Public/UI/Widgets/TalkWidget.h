// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TalkWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UTalkWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TalkText;
	
public:
	void Init(FText NewText);
};
