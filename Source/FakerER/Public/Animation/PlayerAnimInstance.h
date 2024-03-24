// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */

enum class EWeaponType : uint8;
UCLASS()
class FAKEER_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
	void AnimNotify_StartDamage();
	UFUNCTION()
	void AnimNotify_EndDamage();
	UFUNCTION()
	void AnimNotify_FinishRoll();
	UFUNCTION()
	void AnimNotify_EndAttack();
	UFUNCTION()
	void AnimNotify_ContinueAttack();
	UFUNCTION()
	void AnimNotify_UnEquipRight();
	UFUNCTION()
	void AnimNotify_EquipRight();
	UFUNCTION()
	void AnimNotify_UnEquipLeft();
	UFUNCTION()
	void AnimNotify_EquipLeft();
	UFUNCTION()
	void AnimNotify_StartUseItem();
	UFUNCTION()
	void AnimNotify_EndUseItem();
	UFUNCTION()
	void AnimNotify_UseItem();
	UFUNCTION()
	void AnimNotify_CanAttackRotate();
	UFUNCTION()
	void AnimNotify_CannotAttackRotate();
	
protected:
	UPROPERTY(BlueprintReadOnly)
	bool  bIsSprint;
	UPROPERTY(BlueprintReadOnly)
	bool bIsRoll;
	UPROPERTY(BlueprintReadOnly)
	bool bIsLock;
	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	float InputX;
	UPROPERTY(BlueprintReadOnly)
	float InputY;
	UPROPERTY(BlueprintReadOnly)
	bool bIsHoldWeapon;
	UPROPERTY(BlueprintReadOnly)
	EWeaponType WeaponType;
	UPROPERTY(BlueprintReadOnly)
	bool bIsBothHand;	
	
};
