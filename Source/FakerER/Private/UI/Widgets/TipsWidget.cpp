// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/TipsWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UTipsWidget::SetTips(UTexture2D* Icon, FText Text)
{
	if (Icon)
	{
		KeyIcon->SetBrushFromTexture(Icon);
        TipsText->SetText(Text);
	}

}
