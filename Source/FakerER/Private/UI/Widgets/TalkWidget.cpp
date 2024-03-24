// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/TalkWidget.h"

#include "Components/TextBlock.h"

void UTalkWidget::Init(FText NewText)
{
	TalkText->SetText(NewText);
}
