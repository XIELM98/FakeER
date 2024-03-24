// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ERCharacterBase.h"
#include "ERAICharacterBase.generated.h"

/**
 * 
 */

UENUM()
enum class EAIState : uint8
{
	NPC,Enemy,Businessman
};

UCLASS()
class FAKEER_API AERAICharacterBase : public AERCharacterBase
{
	GENERATED_BODY()
	AERAICharacterBase();
	
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void ChangeToEnemy();
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void EquipPackage();
	
protected:
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HPWidget;
	UPROPERTY(EditAnywhere)
	class UHPWidget* HPBar;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere,Category = Sounds)
	class USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere)
	EAIState CurrentAIState;
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere)
	FName NPCID;

	UPROPERTY()
	class UTalkWidget* TalkWidget;
	int32 HitIndex;
	int32 TalkIndex;
	
public:
	UBehaviorTree* GetBehaviorTree() const {return BehaviorTree;}
	EAIState GetAIState() const {return CurrentAIState;}

	void Talk(int32 Index);
	void BattleTalk(int32 Index);
	void ShopTalk(int32 Index);
	void NormalTalk(int32 Index);
	
	int32 GetTalkIndex() const {return TalkIndex;}
};
