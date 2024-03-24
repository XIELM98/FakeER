// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ERPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API AERPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	virtual void UpdateCamera(float DeltaTime) override;
	void LockOn();
	void LockOff();
};
