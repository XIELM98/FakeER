// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/WeaponPanelWidget.h"

#include "ERHUD.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ERSubsystem.h"
#include "UI/EquipUserWidget.h"
#include "UI/MenuUserWidget.h"

#define SETCOLOR(TextBlock,Member)			if (OldWeaponInfo && OldWeaponInfo->Member < WeaponInfo->Member)\
				{\
					TextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));\
				}\
if (OldWeaponInfo && OldWeaponInfo->Member > WeaponInfo->Member)\
{\
	TextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Red));\
}\


void UWeaponPanelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitWeaponPanel();
}

FText UWeaponPanelWidget::GetAbnormalText(EAbnormalState State, int32 Num)
{
	switch (State)
	{
	case EAbnormalState::Blooding :
		return FText::Format(NSLOCTEXT("WeaponPanel","WeaponAbnormal","累计出血量表（{0}）"),Num);
	case EAbnormalState::Death :
		return FText::Format(NSLOCTEXT("WeaponPanel","WeaponAbnormal","累计即死量表（{0}）"),Num);
	case EAbnormalState::Poison :
		return FText::Format(NSLOCTEXT("WeaponPanel","WeaponAbnormal","累计中毒量表（{0}）"),Num);
	}
	return NSLOCTEXT("WeaponPanel","WeaponAbnormal","-");
}

void UWeaponPanelWidget::InitWeaponPanel()
{
	UMaterialInterface* Blank = LoadObject<UMaterialInterface>(this,TEXT("/Script/Engine.Material'/Game/FakeER/Materials/M_Null.M_Null'")); 
	WeaponName->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	WeaponType->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	BattleAshName->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	CostMana->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	WeaponWeight->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	AdditionPower->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	AdditionAgile->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	AdditionIntelligence->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	AdditionBelief->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	NeedPower->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	NeedAgile->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	NeedIntelligence->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	NeedBelief->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	NeedPower->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	NeedAgile->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	NeedIntelligence->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	NeedBelief->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	AbnormalState1->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	AbnormalState2->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	AbnormalState3->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	PhysicalAttack->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	MagicAttack->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	FireAttack->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	LightingAttack->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	ExecuteNum->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	PhysicalDefend->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	MagicDefend->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	FireDefend->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	LightingDefend->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	DefendStrength->SetText(NSLOCTEXT("WeaponPanel","Init","-"));
	
	PhysicalCalculate->SetVisibility(ESlateVisibility::Hidden);
	PhysicalAdditionAttack->SetVisibility(ESlateVisibility::Hidden);
	PhysicalCalculate->SetText(NSLOCTEXT("WeaponPanel","Cal","+"));
	MagicCalculate->SetVisibility(ESlateVisibility::Hidden);
	MagicAdditionAttack->SetVisibility(ESlateVisibility::Hidden);
	MagicCalculate->SetText(NSLOCTEXT("WeaponPanel","Cal","+"));
	FireCalculate->SetVisibility(ESlateVisibility::Hidden);
	FireAdditionAttack->SetVisibility(ESlateVisibility::Hidden);
	FireCalculate->SetText(NSLOCTEXT("WeaponPanel","Cal","+"));
	LightingCalculate->SetVisibility(ESlateVisibility::Hidden);
	LightingAdditionAttack->SetVisibility(ESlateVisibility::Hidden);
	LightingCalculate->SetText(NSLOCTEXT("WeaponPanel","Cal","+"));
	PhysicalCalculate->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	PhysicalAdditionAttack->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	MagicCalculate->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	MagicAdditionAttack->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	FireCalculate->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	FireAdditionAttack->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	LightingCalculate->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	LightingAdditionAttack->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	CostMana->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	WeaponWeight->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	PhysicalAttack->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	MagicAttack->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	FireAttack->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	LightingAttack->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	ExecuteNum->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	PhysicalDefend->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	MagicDefend->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	FireDefend->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	LightingDefend->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	DefendStrength->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	AdditionPower->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	AdditionAgile->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	AdditionIntelligence->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	AdditionBelief->SetColorAndOpacity(FSlateColor(FLinearColor::White));


	WeaponIcon->SetBrushFromMaterial(Blank);
}

FText UWeaponPanelWidget::CalAdditionLevel(int32 Num)
{
	if (Num <= 0)
	{
		return NSLOCTEXT("WeaponPanel","Addition","-");
	}
	else if (Num <= 10)
	{
		return NSLOCTEXT("WeaponPanel","Addition","D");
	}
	else if (Num <= 20)
	{
		return NSLOCTEXT("WeaponPanel","Addition","C");
	}
	else if (Num <= 30)
	{
		return NSLOCTEXT("WeaponPanel","Addition","B");
	}
	else if (Num <= 40)
	{
		return NSLOCTEXT("WeaponPanel","Addition","A");
	}
	else if (Num > 40)
	{
		return NSLOCTEXT("WeaponPanel","Addition","S");
	}
	return NSLOCTEXT("WeaponPanel","Addition","-");
	
}

void UWeaponPanelWidget::UpdateWeaponPanel(int32 ID)
{
	InitWeaponPanel();
	if (ID == -1)
	{
		return;
	}
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ID))
	{
		if (FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo))
		{
			FWeaponInfo* OldWeaponInfo = nullptr;
			if (UEquipUserWidget* EquipUserWidget = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD())->GetMenuUserWidget()->GetEquipWidget())
			{
				if (EquipUserWidget->GetChooseGrid() && EquipUserWidget->GetChooseGrid()->GetBindItemID() != -1)
				{
					FItemInfo* OldItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(EquipUserWidget->GetChooseGrid()->GetBindItemID());
					OldWeaponInfo = reinterpret_cast<FWeaponInfo*>(OldItemInfo);
				}
			}
			if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
			{
				FCharacterAttribute* PlayerAttribute = PlayerCharacter->GetCharacterAttribute();
				WeaponName->SetText(WeaponInfo->Name);
				switch (WeaponInfo->WeaponType)
				{
				case EWeaponType::Axe:WeaponType->SetText(NSLOCTEXT("WeaponPanel","WeaponType","斧"));break;
				case EWeaponType::Bell:WeaponType->SetText(NSLOCTEXT("WeaponPanel","WeaponType","印记"));break;
				case EWeaponType::Bow:WeaponType->SetText(NSLOCTEXT("WeaponPanel","WeaponType","弓"));break;
				case EWeaponType::Crossbow:WeaponType->SetText(NSLOCTEXT("WeaponPanel","WeaponType","弩"));break;
				case EWeaponType::Dagger:WeaponType->SetText(NSLOCTEXT("WeaponPanel","WeaponType","短刀"));break;
				case EWeaponType::Spear:WeaponType->SetText(NSLOCTEXT("WeaponPanel","WeaponType","枪"));break;
				case EWeaponType::Staff:WeaponType->SetText(NSLOCTEXT("WeaponPanel","WeaponType","法杖"));break;
				case EWeaponType::Sword:WeaponType->SetText(NSLOCTEXT("WeaponPanel","WeaponType","剑"));break;
				}
				if (WeaponInfo->BattleAshID == -1)
				{
					BattleAshName->SetText(NSLOCTEXT("WeaponPanel","BattleAshName","无"));
					CostMana->SetText(NSLOCTEXT("WeaponPanel","CostMana","0"));
				}
				else
				{
					if (FItemInfo* BattleAshItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(WeaponInfo->BattleAshID + BATTLEASHINDEX))
					{
						if (FBattleAsh* BattleAsh = reinterpret_cast<FBattleAsh*>(BattleAshItemInfo))
						{
							BattleAshName->SetText(BattleAsh->Name);
							if (OldWeaponInfo && OldWeaponInfo->CostMana > WeaponInfo->CostMana)
							{
								CostMana->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
							}
							if (OldWeaponInfo && OldWeaponInfo->CostMana < WeaponInfo->CostMana)
							{
								CostMana->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
							}
							CostMana->SetText(FText::AsNumber(BattleAsh->CostMana));
						}
					}
				}
				if (OldWeaponInfo && OldWeaponInfo->Weight > WeaponInfo->Weight)
				{
					WeaponWeight->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));
				}
				if (OldWeaponInfo && OldWeaponInfo->Weight < WeaponInfo->Weight)
				{
					WeaponWeight->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
				}
				WeaponWeight->SetText(FText::AsNumber(WeaponInfo->Weight));
				SETCOLOR(PhysicalAttack,PhysicalAttack)
				PhysicalAttack->SetText(FText::AsNumber(WeaponInfo->PhysicalAttack));
				if (WeaponInfo->PhysicalAttack > 0 )
				{
					if (WeaponInfo->AdditionPhysicalAttack >= 0)
					{
						PhysicalCalculate->SetVisibility(ESlateVisibility::Visible);
						PhysicalAdditionAttack->SetVisibility(ESlateVisibility::Visible);
						PhysicalAdditionAttack->SetText(FText::AsNumber(WeaponInfo->AdditionPhysicalAttack));
						SETCOLOR(PhysicalAdditionAttack,AdditionPhysicalAttack);
					}
					else
					{
						PhysicalCalculate->SetVisibility(ESlateVisibility::Visible);
						PhysicalCalculate->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
						PhysicalCalculate->SetText(NSLOCTEXT("WeaponPanel","Cal","-"));
						PhysicalAdditionAttack->SetVisibility(ESlateVisibility::Visible);
						PhysicalAdditionAttack->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
						PhysicalAdditionAttack->SetText(FText::AsNumber(FMath::Abs(WeaponInfo->AdditionPhysicalAttack)));
					}
				}
				SETCOLOR(MagicAttack,MagicAttack)
				MagicAttack->SetText(FText::AsNumber(WeaponInfo->MagicAttack));
				if (WeaponInfo->MagicAttack > 0)
				{
					if (WeaponInfo->AdditionMagicAttack >= 0)
					{
						MagicCalculate->SetVisibility(ESlateVisibility::Visible);
						MagicAdditionAttack->SetVisibility(ESlateVisibility::Visible);
						MagicAdditionAttack->SetText(FText::AsNumber(WeaponInfo->AdditionMagicAttack));
						SETCOLOR(MagicAdditionAttack,AdditionMagicAttack)
					}
					else
					{
						MagicCalculate->SetVisibility(ESlateVisibility::Visible);
						MagicCalculate->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
						MagicCalculate->SetText(NSLOCTEXT("WeaponPanel","Cal","-"));
						MagicAdditionAttack->SetVisibility(ESlateVisibility::Visible);
						MagicAdditionAttack->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
						MagicAdditionAttack->SetText(FText::AsNumber(FMath::Abs(WeaponInfo->AdditionMagicAttack)));
					}
				}
				SETCOLOR(FireAttack,FireAttack)
				FireAttack->SetText(FText::AsNumber(WeaponInfo->FireAttack));
				if (WeaponInfo->FireAttack > 0 )
				{
					if (WeaponInfo->AdditionFireAttack >= 0)
					{
						FireCalculate->SetVisibility(ESlateVisibility::Visible);
						FireAdditionAttack->SetVisibility(ESlateVisibility::Visible);
						FireAdditionAttack->SetText(FText::AsNumber(WeaponInfo->AdditionFireAttack));
						SETCOLOR(FireAdditionAttack,AdditionFireAttack)
					}
					else
					{
						FireCalculate->SetVisibility(ESlateVisibility::Visible);
						FireCalculate->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
						FireCalculate->SetText(NSLOCTEXT("WeaponPanel","Cal","-"));
						FireAdditionAttack->SetVisibility(ESlateVisibility::Visible);
						FireAdditionAttack->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
						FireAdditionAttack->SetText(FText::AsNumber(FMath::Abs(WeaponInfo->AdditionFireAttack)));
					}
				}
				SETCOLOR(LightingAttack,LightingAttack)
				LightingAttack->SetText(FText::AsNumber(WeaponInfo->LightingAttack));
				if (WeaponInfo->LightingAttack > 0)
				{
					if (WeaponInfo->AdditionLightingAttack >= 0)
					{
						LightingCalculate->SetVisibility(ESlateVisibility::Visible);
						LightingAdditionAttack->SetVisibility(ESlateVisibility::Visible);
						LightingAdditionAttack->SetText(FText::AsNumber(WeaponInfo->AdditionLightingAttack));
						SETCOLOR(LightingAdditionAttack,AdditionLightingAttack)
					}
					else
					{
						LightingCalculate->SetVisibility(ESlateVisibility::Visible);
						LightingCalculate->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
						LightingCalculate->SetText(NSLOCTEXT("WeaponPanel","Cal","-"));
						LightingAdditionAttack->SetVisibility(ESlateVisibility::Visible);
						LightingAdditionAttack->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
						LightingAdditionAttack->SetText(FText::AsNumber(FMath::Abs(WeaponInfo->AdditionLightingAttack)));
					}
				}
				SETCOLOR(ExecuteNum,Execute)
				SETCOLOR(PhysicalDefend,PhysicalDefend)
				SETCOLOR(MagicDefend,MagicDefend)
				SETCOLOR(FireDefend,FireDefend)
				SETCOLOR(LightingDefend,LightingDefend)
				SETCOLOR(DefendStrength,DefendStrength)
				ExecuteNum->SetText(FText::AsNumber(WeaponInfo->Execute));
				PhysicalDefend->SetText(FText::AsNumber(WeaponInfo->PhysicalDefend));
				MagicDefend->SetText(FText::AsNumber(WeaponInfo->MagicDefend));
				FireDefend->SetText(FText::AsNumber(WeaponInfo->FireDefend));
				LightingDefend->SetText(FText::AsNumber(WeaponInfo->LightingDefend));
				DefendStrength->SetText(FText::AsNumber(WeaponInfo->DefendStrength));
				if (WeaponInfo->AdditionPower > 0)
				{
					SETCOLOR(AdditionPower,AdditionPower)
					AdditionPower->SetText(CalAdditionLevel(WeaponInfo->AdditionPower));
				}
				if (WeaponInfo->AdditionAgile > 0)
				{
					SETCOLOR(AdditionAgile,AdditionAgile)
					AdditionAgile->SetText(CalAdditionLevel(WeaponInfo->AdditionAgile));

				}
				if (WeaponInfo->AdditionIntelligence > 0)
				{
					SETCOLOR(AdditionIntelligence,AdditionIntelligence)
					AdditionIntelligence->SetText(CalAdditionLevel(WeaponInfo->AdditionIntelligence));
				}
				if (WeaponInfo->AdditionBelief > 0)
				{
					SETCOLOR(AdditionBelief,AdditionBelief)
					AdditionBelief->SetText(CalAdditionLevel(WeaponInfo->AdditionBelief));
				}
				
				
				NeedPower->SetText(FText::AsNumber(WeaponInfo->NeedPower));
				if (WeaponInfo->NeedPower > PlayerAttribute->Power)
				{
					NeedPower->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
				}
				NeedAgile->SetText(FText::AsNumber(WeaponInfo->NeedAgile));
				if (WeaponInfo->NeedAgile > PlayerAttribute->Agile)
				{
					NeedAgile->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
				}
				NeedIntelligence->SetText(FText::AsNumber(WeaponInfo->NeedIntelligence));
				if (WeaponInfo->NeedIntelligence > PlayerAttribute->Intelligence)
				{
					NeedIntelligence->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
				}
				NeedBelief->SetText(FText::AsNumber(WeaponInfo->NeedBelief));
				if (PlayerAttribute->Belief < WeaponInfo->NeedBelief)
				{
					NeedBelief->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
				}
				
				if (WeaponInfo->AbnormalState.Num() > 0)
				{
					AbnormalState1->SetText(NSLOCTEXT("WeaponPanel","WeaponAbnormal","-"));
					AbnormalState2->SetText(NSLOCTEXT("WeaponPanel","WeaponAbnormal","-"));
					AbnormalState3->SetText(NSLOCTEXT("WeaponPanel","WeaponAbnormal","-"));
					int32 i = 1;
					for (auto Key : WeaponInfo->AbnormalState)
					{
						FText Text = GetAbnormalText(Key.Key,Key.Value);
						if (i == 1)
						{
							AbnormalState1->SetText(Text);
							i++;
							continue;	
						}
						if (i == 2)
						{
							AbnormalState2->SetText(Text);
							i++;
							continue;	
						}
						if (i == 3)
						{
							AbnormalState3->SetText(Text);
							i++;
							continue;	
						}
					}
				}
				WeaponIcon->SetBrushFromTexture(WeaponInfo->Icon);
			}
		}
	}
}

#undef SETCOLOR