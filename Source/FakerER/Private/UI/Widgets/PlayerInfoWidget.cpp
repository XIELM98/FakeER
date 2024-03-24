// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PlayerInfoWidget.h"

#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

void UPlayerInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UPlayerInfoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		HPBar->SetPercent(PlayerCharacter->GetCharacterPanel()->NowHP / PlayerCharacter->GetCharacterPanel()->MaxHP);
		MPBar->SetPercent(PlayerCharacter->GetCharacterPanel()->NowMana / PlayerCharacter->GetCharacterPanel()->MaxMana);
		EnduranceBar->SetPercent(PlayerCharacter->GetCharacterPanel()->NowEndurance / PlayerCharacter->GetCharacterPanel()->MaxEndurance);
	}
}

void UPlayerInfoWidget::LevelUp()
{
	HPBar->SetRenderScale(FVector2D(1,1));
	MPBar->SetRenderScale(FVector2D(1,1));
	EnduranceBar->SetRenderScale(FVector2D(1,1));
	
}
