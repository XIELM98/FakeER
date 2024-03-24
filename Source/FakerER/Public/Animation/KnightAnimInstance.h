// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Subsystem/ERSubsystem.h"
#include "KnightAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API UKnightAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldWeapon;
	UPROPERTY(BlueprintReadOnly)
	EWeaponType WeaponType;
	UPROPERTY(BlueprintReadOnly)
	bool bIsBothHand;
	UPROPERTY(BlueprintReadOnly)
	bool bIsSit;
};
