// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC//ERAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/ERCharacterBase.h"
#include "Characters/NPC//ERAICharacterBase.h"
#include "Perception/AIPerceptionComponent.h"

AERAIController::AERAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPercetionComp"));
}

void AERAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AERAICharacterBase* AICharacter = Cast<AERAICharacterBase>(InPawn))
	{
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this,&AERAIController::OnReceiveTargetPerception);
		if (AICharacter->GetBehaviorTree())
		{
			RunBehaviorTree(AICharacter->GetBehaviorTree());
			GetBlackboardComponent()->SetValueAsBool(TEXT("IsNPC"),AICharacter->GetAIState() != EAIState::Enemy);
			GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPosition"),InPawn->GetActorLocation());
			GetBlackboardComponent()->SetValueAsVector(TEXT("TargetPosition"),InPawn->GetActorLocation() + InPawn->GetActorForwardVector() * 800);
		}
	}
}

void AERAIController::OnUnPossess()
{
	if (UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent))
	{
		BehaviorTreeComponent->StopTree();
	}
	Super::OnUnPossess();
}

void AERAIController::OnReceiveTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{
	
}
