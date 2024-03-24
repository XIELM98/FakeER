// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/ERPlayerCameraManager.h"

#include "ERPlayerController.h"
#include "Characters/Player/ERPlayerCharacter.h"

void AERPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);
	if (AERPlayerCharacter* Player = Cast<AERPlayerCharacter>(GetOwningPlayerController()->GetPawn()))
	{
		if (Player->GetIsLock())
		{
			LockOn();
		}
		else
		{
			LockOff();
		}
		
	}
}

void AERPlayerCameraManager::LockOn()
{
	
}

void AERPlayerCameraManager::LockOff()
{
	
}
