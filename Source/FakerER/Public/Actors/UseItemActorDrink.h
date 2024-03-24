// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/UseItemActor.h"
#include "UseItemActorDrink.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API AUseItemActorDrink : public AUseItemActor
{
	GENERATED_BODY()

protected:
	virtual void OnItemUsed(int32 ID) override;
	
};
