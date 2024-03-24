// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ERAIController.generated.h"

struct FAIStimulus;
/**
 * 
 */
UCLASS()
class FAKEER_API AERAIController : public AAIController
{
	GENERATED_BODY()

	AERAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
	UFUNCTION()
	void OnReceiveTargetPerception(AActor* Actor, FAIStimulus Stimulus);
	
protected:
	UPROPERTY()
	UAIPerceptionComponent* AIPerceptionComponent;
};
