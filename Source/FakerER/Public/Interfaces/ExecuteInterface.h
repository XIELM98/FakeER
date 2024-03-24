// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ExecuteInterface.generated.h"

class AERCharacterBase;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UExecuteInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FAKEER_API IExecuteInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual  void BeExecute(AERCharacterBase* Attacker) = 0;

	UFUNCTION()
	virtual void BeBackStab(AERCharacterBase* Attacker) = 0;
	
};
