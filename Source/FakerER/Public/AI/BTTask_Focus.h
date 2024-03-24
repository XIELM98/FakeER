// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Focus.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UBTTask_Focus : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_Focus();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	bool bIsFocus;
};
