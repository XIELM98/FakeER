// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_FindRandomPosition.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Characters/ERCharacterBase.h"

UBTTaskNode_FindRandomPosition::UBTTaskNode_FindRandomPosition()
{
	NodeName = TEXT("随机找点");
	Radius = 500.f;
	OriginPositionKey.AddVectorFilter(this,TEXT("OriginPosition"));
	TargetPositionKey.AddVectorFilter(this,TEXT("TargetPosition"));
	OriginPositionKey.AddObjectFilter(this,TEXT("OriginActor"),AERCharacterBase::StaticClass());
}

EBTNodeResult::Type UBTTaskNode_FindRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OriginPositionKey.IsNone() || TargetPositionKey.IsNone())
	{
		return EBTNodeResult::Failed;
	}
	FVector OriginPos;
	if (OriginPositionKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(OriginPositionKey.GetSelectedKeyID())))
		{
			OriginPos = CharacterBase->GetActorLocation();
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		OriginPos = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(OriginPositionKey.GetSelectedKeyID());
	}

	FVector TargetPos;
	if (UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(OwnerComp.GetWorld(),OriginPos,TargetPos,Radius))
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(TargetPositionKey.GetSelectedKeyID(),TargetPos);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UBTTaskNode_FindRandomPosition::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	if(UBlackboardData* BBData = GetBlackboardAsset())
	{
		OriginPositionKey.ResolveSelectedKey(*BBData);
		TargetPositionKey.ResolveSelectedKey(*BBData);
	}
}
