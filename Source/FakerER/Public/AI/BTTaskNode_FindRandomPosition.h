// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindRandomPosition.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UBTTaskNode_FindRandomPosition : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTaskNode_FindRandomPosition();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector OriginPositionKey;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetPositionKey;
	UPROPERTY(EditAnywhere)
	float Radius;
	
};
