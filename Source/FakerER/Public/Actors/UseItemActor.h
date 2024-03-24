// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "UseItemActor.generated.h"

UCLASS()
class FAKEER_API AUseItemActor : public AItemActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUseItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnItemUsed(int32 ID);
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;
	
	UPROPERTY()
	class AERCharacterBase* MyMaster;

	bool bShouldDelete;
	bool bIsLeaveMaster;
public:
	void SetupMasterAndID(AERCharacterBase* Master,int32 ID);
	bool GetShouldDelete() const {return bShouldDelete;}
	
};
