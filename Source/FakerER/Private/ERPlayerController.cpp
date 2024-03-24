// Fill out your copyright notice in the Description page of Project Settings.


#include "ERPlayerController.h"

#include "Characters/Player/ERPlayerCameraManager.h"

AERPlayerController::AERPlayerController()
{
	PlayerCameraManagerClass = AERPlayerCameraManager::StaticClass();
}

