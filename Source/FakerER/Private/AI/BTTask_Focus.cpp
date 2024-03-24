// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Focus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Characters/ERCharacterBase.h"
#include "Characters/Player/ERPlayerCharacter.h"

UBTTask_Focus::UBTTask_Focus()
{
	NodeName = TEXT("锁定目标");
	BlackboardKey.AddObjectFilter(this,TEXT("BlackboardKey"),AERCharacterBase::StaticClass());
	bIsFocus = true;
}

EBTNodeResult::Type UBTTask_Focus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (BlackboardKey.IsNone())
	{
		return EBTNodeResult::Failed;
	}
	if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID())))
	{
		if (bIsFocus)
		{
			OwnerComp.GetAIOwner()->SetFocus(PlayerCharacter);
		}
		else
		{
			OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
	return EBTNodeResult::Succeeded;
}
