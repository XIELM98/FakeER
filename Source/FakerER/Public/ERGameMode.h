// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ERGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API AERGameMode : public AGameMode
{
	GENERATED_BODY()

	AERGameMode();

protected:
	UFUNCTION(Exec)
	void RequestHttpGet(const FString& Url);
	UFUNCTION(Exec)
	void RequestHttpPost(const FString& Url,const FString& Msg);

	UFUNCTION(Exec)
	void MyThread();
	

protected:
	TSharedPtr<class FHttpHelper> HttpHelper;
	TSharedPtr<class FMyRunnable> MyRunnable;
	
	// UFUNCTION(Exec)
	// void GetJson();
	// UFUNCTION(Exec)
	// void SetJson();
	// UFUNCTION(Exec)
	// void SetActor();

	
};
