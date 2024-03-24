// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "..\Interfaces\ExecuteInterface.h"
#include "BreakableActor.generated.h"


class UGeometryCollectionComponent;

UCLASS()
class FAKEER_API ABreakableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBreak(const FChaosBreakEvent& BreakEvent);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UGeometryCollectionComponent* GeometryCollectionComponent; 

	UPROPERTY(EditAnywhere)
	class USoundBase* BreakSound;
};
