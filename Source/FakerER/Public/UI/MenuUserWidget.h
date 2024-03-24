// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()


protected:

	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	void OpenEquipWidget();
	UFUNCTION()
	void OpenPackageWidget();
	UFUNCTION()
	void OpenStateWidget();
	UFUNCTION()
	void OpenConfigWidget();
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UButton* EquipWidgetButton;
	UPROPERTY(EditAnywhere)
	class UEquipUserWidget* EquipWidget;
	UPROPERTY(meta=(BindWidget))
	class UButton* PackageWidgetButton;
	UPROPERTY(EditAnywhere)
	class UPackageUserWidget* PackageWidget;
	UPROPERTY(meta=(BindWidget))
	class UButton* StateWidgetButton;
	UPROPERTY(EditAnywhere)
	class UStateUserWidget* StateWidget;
	UPROPERTY(meta=(BindWidget))
	class UButton* ConfigWidgetButton;
	UPROPERTY(EditAnywhere)
	class UConfigUserWidget* ConfigWidget;

public:
	UEquipUserWidget* GetEquipWidget() const {return EquipWidget;}
	UPackageUserWidget* GetPackageWidget() const{return PackageWidget;}
	UConfigUserWidget* GetConfigWidget() const{return ConfigWidget;}
	
};
