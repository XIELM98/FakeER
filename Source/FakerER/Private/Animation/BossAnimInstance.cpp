// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BossAnimInstance.h"

#include "Characters/Enemy/ERBossBase.h"
#include "GameFramework/PawnMovementComponent.h"

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AERBossBase* Boss = Cast<AERBossBase>(TryGetPawnOwner()))
	{
		Speed = Boss->GetMovementComponent()->Velocity.Length();
	}
}
