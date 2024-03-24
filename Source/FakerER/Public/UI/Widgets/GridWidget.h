// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "GridWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UGridWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	void OnGridHovered();
	UFUNCTION()
	void OnGridClicked();
	
	void EquipHover();
	void ChooseHover();
	void PackageHover();
	
	void EquipClick();
	void ChooseClick();
	void PackageClick();

protected:
	UPROPERTY(meta=(BindWidget))
	UImage* Icon;
	UPROPERTY(meta=(BindWidget))
	UImage* BackGroundIcon;
	UPROPERTY(meta=(BindWidget))
	UImage* BackGroundImage;
	UPROPERTY(meta=(BindWidget))
	class UButton* GridButton;
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemNum;
	UPROPERTY(meta=(BindWidget))
	UImage* GrayImage;
	
	FText GridName;
	int32 BindItemID;
	bool bIsOption;

	
public:
	void Init(class UTexture2D* InBackgroundImage, FText InGridName, UTexture2D* InBackGroundIcon =nullptr);
	void BindItem(int32 ID, int32 Num = -1);
	int32 GetBindItemID() const {return BindItemID;}
	void SetGridUnUsable() const {GrayImage->SetVisibility(ESlateVisibility::Visible);}
	void SetGridUsable() const {GrayImage->SetVisibility(ESlateVisibility::Hidden);}
	void SetIcon(UTexture2D* NewIcon) const {Icon->SetBrushFromTexture(NewIcon);}
	void SetIsOption(bool NewIsItem) {bIsOption = NewIsItem;}

	UButton* GetButton() const {return GridButton;}
};
