// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ERCharacterBase.h"
#include "..\..\Interfaces\ExecuteInterface.h"
#include "EREnemyBase.generated.h"

UCLASS()
class FAKEER_API AEREnemyBase : public AERCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEREnemyBase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HPWidgetComponent;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UHPWidget>  HPWidgetClass;
	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;
	UPROPERTY()
	class UHPWidget* HPWidget;
	
};
