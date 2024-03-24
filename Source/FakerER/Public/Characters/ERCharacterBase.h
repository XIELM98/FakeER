// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ERCharacterBase.generated.h"

UENUM()
enum class ECharacterState : uint8
{
	Normal,
	LeftAttack,
	RightAttack,
	Hit,
	Drink,
	Roll,
	Guide,
	Guard,
	Execute
};


//角色属性
USTRUCT()
struct FCharacterAttribute : public FTableRowStyle
{
	GENERATED_BODY()

	//等级，血，绿，蓝，力量，敏捷，智力，信仰
	UPROPERTY(EditAnywhere)
	int32 Level;
	UPROPERTY(EditAnywhere)
	int32 Red;
	UPROPERTY(EditAnywhere)
	int32 Green;
	UPROPERTY(EditAnywhere)
	int32 Blue;
	UPROPERTY(EditAnywhere)
	int32 Power;
	UPROPERTY(EditAnywhere)
	int32 Agile;
	UPROPERTY(EditAnywhere)
	int32 Intelligence;
	UPROPERTY(EditAnywhere)
	int32 Belief;
	
};

USTRUCT()
struct FCharacterPanel
{
	GENERATED_BODY()

	//血，绿，蓝，攻击力，防御，记忆空格，攻击力（斩，打，刺，火，魔，雷），防御力，待定（抵抗力，装备重量，掉宝），持有卢恩，升级所需卢恩
	float MaxHP;
	float NowHP;
	float MaxMana;
	float NowMana;
	float NowEndurance;
	float MaxEndurance;
	float MaxEquipWeight;
	float NowEquipWeight;
	int32 MemorySpace;
	float MaxToughness;//韧性
	float NowToughness;//韧性
	float ImpactDefend;
	float RightPhysicalAttack;
	float RightFireAttack;
	float RightMagicAttack;
	float RightLightingAttack;
	float LeftPhysicalAttack;
	float LeftFireAttack;
	float LeftMagicAttack;
	float LeftLightingAttack;
	float PhysicalDefend;
	float FireDefend;
	float MagicDefend;
	float LightingDefend;
	float BloodingDefend;
	float PoisonDefend;
	float DeathDefend;
};



UCLASS()
class FAKEER_API AERCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AERCharacterBase(const FObjectInitializer& Initializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//KeyFunc
	void UseItem();
	void Roll();
	void Run();
	void OverRun();
	virtual void RightLightAttack();
	void RightHeavyAttack();
	void ChargeAttack();
	void LeftLightAttack();
	void Guard();
	void BattleArt();
	void DoJump();
	void ChangeSpell();
	void ChangeItem();
	void ChangeLeftWeapon();
	void ChangeRightWeapon();
	void RightBothHand();
	void LeftBothHand();
	void ReleaseSpell();

	void InitPlayerPanel();
	void CancelBothHand();
	void CostEndurance(float InEndurance);

	
	void LeaveBattle();
	void AddToughness();
	
protected:
	FTimerHandle DamageTimerHandle;
	FTimerHandle ToughnessTimerHandle;
	
	//Animation
	bool bIsRoll;
	float InputX;
	float InputY;
	bool bIsLock;
	bool bIsBothHand;
	int32 AttackIndex;
	bool bIsRest;
	bool bCanAddEndurance;
	bool AddEnduranceSpeed;
	float RollEndurance;
	
	//Normal
	float HaveRune;
	float NeedRune;
	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	UPROPERTY(EditAnywhere)
	float RunSpeed;

	bool bCanExecute;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LockTag;
	
	UPROPERTY(VisibleAnywhere)
	class UPackageComponent* PackageComponent;
	UPROPERTY(VisibleAnywhere)
	class UERMovementComponent* ERMovementComponent;
	UPROPERTY(EditAnywhere)
	FCharacterAttribute CharacterAttribute;
	UPROPERTY()
	FCharacterPanel CharacterPanel;
	UPROPERTY(EditAnywhere)
	FFloatCurve HPCurve;

	ECharacterState CurrentState;

protected:
	UPROPERTY(EditAnywhere)
	UAnimMontage* HitAnim;
	UPROPERTY(EditAnywhere)
	UAnimMontage* Drink;
	UPROPERTY(EditAnywhere)
	UAnimMontage* PickUp;
	UPROPERTY(EditAnywhere)
	UAnimMontage* EquipLeft;
	UPROPERTY(EditAnywhere)
	UAnimMontage* UnEquipLeft;
	UPROPERTY(EditAnywhere)
	UAnimMontage* EquipRight;
	UPROPERTY(EditAnywhere)
	UAnimMontage* UnEquipRight;
	UPROPERTY(EditAnywhere)
	UAnimMontage* ExecuteAnim;
	UPROPERTY(EditAnywhere)
	UAnimMontage* BackStabAnim;
	
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	bool bShouldEquip;


	void StopMove();
	void StartMove();
	bool GetCanExecute() const {return  bCanExecute;};
	
	//Animation
	bool GetIsRoll() const {return bIsRoll;}
	bool GetIsLock() const {return bIsLock;}
	void FinishRoll() {bIsRoll = false; bCanAddEndurance = true;}
	float GetInputX() const {return InputX;}
	float GetInputY() const {return InputY;}
	void SetIsBothHand(bool NewHand){bIsBothHand = NewHand;}
	bool GetIsBothHand() const {return bIsBothHand;}
	void ClearAttackIndex() {AttackIndex = 0 ; bCanAddEndurance = true;}
	void AddAttackIndex() {AttackIndex++;}
	UAnimMontage* GetEquipRightAnim() const {return EquipRight;}
	UAnimMontage* GetEquipLeftAnim() const {return EquipLeft;}
	bool GetIsRest() const {return bIsRest;};
	void StartAddEndurance() {bCanAddEndurance = true;};
	void StopAddEndurance() {bCanAddEndurance = false;};
	
	//NOrmal
	UPackageComponent* GetPackageComponent() const { return  PackageComponent;}
	FCharacterPanel* GetCharacterPanel()  {return &CharacterPanel;}
	FCharacterAttribute* GetCharacterAttribute()  {return &CharacterAttribute;}

	void SetCharacterState(ECharacterState InState) {CurrentState = InState;}
	ECharacterState GetCharacterState() const {return CurrentState;}
	void BeLocked() const {LockTag->SetVisibility(true);}
	void CancelLocked()const {LockTag->SetVisibility(false);}
	
};
