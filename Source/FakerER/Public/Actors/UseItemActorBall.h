// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/UseItemActor.h"
#include "UseItemActorBall.generated.h"

/**
 * 
 */
UCLASS()
class FAKEER_API AUseItemActorBall : public AUseItemActor
{
	GENERATED_BODY()

protected:
	virtual void OnItemUsed(int32 ID) override;
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
