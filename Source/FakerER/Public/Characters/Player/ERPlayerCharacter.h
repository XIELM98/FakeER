// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "LevelSequenceActor.h"
#include "Characters/ERCharacterBase.h"
#include "Engine/DataTable.h"
#include "ERPlayerCharacter.generated.h"

/**
 * 
 */

class FPlayerCharacter;
class AItemActor;
class AInteractActor;
class ULevelSequence;
class ULevelSequencePlayer;
class AERAICharacterBase;
class ASceneItemsActor;
class ALevelSequenceActor;

USTRUCT()
struct FKeyInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UInputAction* InputAction;
	UPROPERTY(EditAnywhere)
	FText KeyDescribe;
	UPROPERTY(EditAnywhere)
	FKey InputKeyboard;
	UPROPERTY(EditAnywhere)
	FKey DefaultKeyboard;
	UPROPERTY(EditAnywhere)
	FKey InputGamepad;
	UPROPERTY(EditAnywhere)
	FKey DefaultGamepad;
};


UCLASS()
class FAKEER_API AERPlayerCharacter : public AERCharacterBase
{
	GENERATED_BODY()
	AERPlayerCharacter();

	
protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void BindKeys();
	void AddKeyToImc(FName InName);
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	bool IsExecute();
	UFUNCTION()
	void OnExecuteFinished();

	virtual void RightLightAttack() override;
	UFUNCTION(BlueprintImplementableEvent)
	bool BindCharacter(AERPlayerCharacter* Attacker, AERCharacterBase* Hitter, ALevelSequenceActor* SequenceActor);
	
	void Interact();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LockOn();
	void CancelLock();
	bool FindLockEnemy();
	bool SelectLockEnemy();
	void OpenMenu();
	
	void PickUpNearItem();
	void TalkWithNPC();
	void InterWithActor();
	void Test();
	
protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere)
	class UDataTable* KeyInfoData;

	
	bool bIsKeyboard;
	float Sensitivity;//视角灵敏度
	float BuffDamageRate;
	float BuffDefendRate;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ShiftInputAction;

	UPROPERTY(EditAnywhere, Category = "Execute")
	ULevelSequence*  ExecuteSequence;
	UPROPERTY(VisibleAnywhere, Category = "Execute")
	ULevelSequencePlayer* ExecuteSequencePlayer;
	UPROPERTY(VisibleAnywhere, Category = "Execute")
	ALevelSequenceActor* ExecuteSequenceActor; 
	
	UPROPERTY()
	ASceneItemsActor* NearItem;
	UPROPERTY()
	AERAICharacterBase* NearNPC;
	UPROPERTY()
	AInteractActor* NearActor;

	UPROPERTY()
	AERCharacterBase* ExecuteCharacter;
	UPROPERTY(VisibleAnywhere)
	TArray<AERCharacterBase*> LockEnemies;
	UPROPERTY(VisibleAnywhere)
	TArray<float> LockRotation;
	UPROPERTY(VisibleAnywhere)
	TMap<float, AERCharacterBase*>EnemyRotationMap;
	UPROPERTY(VisibleAnywhere)
	AERCharacterBase* LockedEnemy;
	
public:
	USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; };
	UCameraComponent* GetCameraComponent() const { return CameraComponent; };
	void SetNearItem(ASceneItemsActor* NewNearItem) {NearItem = NewNearItem; };
	void SetNearNPC(AERAICharacterBase* NewNearNPC) {NearNPC = NewNearNPC; };
	void SetNearActor(AInteractActor* NewNearActor) {NearActor = NewNearActor; };
	int32 GetHaveRune() const {return HaveRune;}
	
};
