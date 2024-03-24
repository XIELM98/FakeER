// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ERSubsystem.generated.h"

/**
 * 
 */
#define ADDITIONRATE 0.1
#define USEITEMINDEX 0
#define WEAPONINDEX 100
#define ARMORNDEX 200
#define TALISMAXINDEX 300
#define ARRORINDEX 400
#define BOLTINDEX 500
#define BATTLEASHINDEX 600
#define SPELLINDEX 700
#define KEYSINDEX 800

UENUM()
enum class EUseItemType : uint8
{
	Consumable,//消耗品
	NotConsumable,//非消耗品
	Key
	
};

UENUM()
enum class EArmorType : uint8
{
	Helmet,
	Body,
	Hand,
	Foot
};

UENUM()
enum class EAbnormalState : uint8
{
	Blooding,
	Poison,
	Death
};


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Dagger,
	Sword,
	Spear,
	Axe,
	Bow,
	Crossbow,//弩
	Staff,//法杖
	Bell//印记
};

UENUM()
enum class ESpellType : uint8
{
	Neither,
	Both,
	Magic,
	Miracle
};

UENUM()
enum class EItemType : uint8
{
	UseableItem,
	BattleAsh,
	Weapon,
	Spell,
	Arrow,
	Bolt,
	Armor,
	Talisman
};

UENUM()
enum class EItemQuality : uint8
{
	Normal,
	Rare,
	Legendary
};

USTRUCT()
struct FItemInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bIsEquip;
	UPROPERTY(EditAnywhere)
	int32 ID;
	UPROPERTY(EditAnywhere)
	FText Name;
	UPROPERTY(EditAnywhere)
	FText Describe;
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere)
	int32 CostMana;
	UPROPERTY(EditAnywhere)
	float CostEndurance;
	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere)
	USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere)
	EItemType ItemType;
	UPROPERTY(EditAnywhere)
	EItemQuality ItemQuality;
	//Damage
	UPROPERTY(EditAnywhere)
	int32 PhysicalAttack;
	UPROPERTY(EditAnywhere)
	int32 MagicAttack;
	UPROPERTY(EditAnywhere)
	int32 FireAttack;
	UPROPERTY(EditAnywhere)
	int32 LightingAttack;
	UPROPERTY(EditAnywhere)
	float ToughnessAttack;//削韧
	UPROPERTY(EditAnywhere)
	float Impulse;//击退距离
	UPROPERTY(EditAnywhere)
	int32 Impact;//冲击力
	
	FItemInfo(){bIsEquip = false;}
};

USTRUCT()
struct FUseableItem : public FItemInfo
{
	GENERATED_BODY()

	FUseableItem(){ItemType = EItemType::UseableItem;}
	UPROPERTY(EditAnywhere)
	EUseItemType UseItemType;
	UPROPERTY(EditAnywhere)
	FText ItemEffect;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUseItemActor> UseItemClass;
	UPROPERTY(EditAnywhere)
	UAnimMontage* UseAnim;
	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleSystem;
};


USTRUCT()
struct FBattleAsh : public FItemInfo
{
	GENERATED_BODY()
	
	FBattleAsh(){ItemType = EItemType::BattleAsh;}
	
	UPROPERTY(EditAnywhere)
	float DamageRate;

};

USTRUCT()
struct FWeaponInfo : public FItemInfo
{
	GENERATED_BODY()

	FWeaponInfo()
	{
		ItemType = EItemType::Weapon;
		Execute = 100;
		BattleAshID = -1;
	}
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeaponActor> WeaponClass;
	UPROPERTY(EditAnywhere)
	int32 PhysicalDefend;
	UPROPERTY(EditAnywhere)
	int32 MagicDefend;
	UPROPERTY(EditAnywhere)
	int32 FireDefend;
	UPROPERTY(EditAnywhere)
	int32 LightingDefend;
	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;
	UPROPERTY(EditAnywhere)
	ESpellType SpellType;
	UPROPERTY(EditAnywhere)
	int32 BattleAshID;
	UPROPERTY(EditAnywhere)
	int32 NeedPower;
	UPROPERTY(EditAnywhere)
	int32 NeedAgile;
	UPROPERTY(EditAnywhere)
	int32 NeedIntelligence;
	UPROPERTY(EditAnywhere)
	int32 NeedBelief;
	UPROPERTY(EditAnywhere)
	int32 AdditionPower;
	UPROPERTY(EditAnywhere)
	int32 AdditionAgile;
	UPROPERTY(EditAnywhere)
	int32 AdditionIntelligence;
	UPROPERTY(EditAnywhere)
	int32 AdditionBelief;
	UPROPERTY(EditAnywhere)
	int32 AdditionPhysicalAttack;
	UPROPERTY(EditAnywhere)
	int32 AdditionMagicAttack;
	UPROPERTY(EditAnywhere)
	int32 AdditionFireAttack;
	UPROPERTY(EditAnywhere)
	int32 AdditionLightingAttack;
	UPROPERTY(EditAnywhere)
	TMap<EAbnormalState,int32> AbnormalState;
	UPROPERTY(EditAnywhere)
	int32 Execute; //处决倍率
	UPROPERTY(EditAnywhere)
	float DefendStrength;
	UPROPERTY(EditAnywhere)
	float Weight;
};

USTRUCT()
struct FSpellInfo : public FItemInfo
{
	GENERATED_BODY()

	FSpellInfo(){ItemType = EItemType::Spell;}
	UPROPERTY(EditAnywhere)
	ESpellType SpellType;
	UPROPERTY(EditAnywhere)
	int32 CostMemorySpace;
	UPROPERTY(EditAnywhere)
	FText SpellEffect;
	UPROPERTY(EditAnywhere)
	int32 NeedIntelligence;
	UPROPERTY(EditAnywhere)
	int32 NeedBelief;
};

USTRUCT()
struct FArmorInfo : public FItemInfo
{
	GENERATED_BODY()

	FArmorInfo(){ItemType = EItemType::Armor;}
	UPROPERTY(EditAnywhere)
	int32 PhysicalDefend;
	UPROPERTY(EditAnywhere)
	int32 MagicDefend;
	UPROPERTY(EditAnywhere)
	int32 FireDefend;
	UPROPERTY(EditAnywhere)
	int32 LightingDefend;
	UPROPERTY(EditAnywhere)
	int32 BloodingDefend;
	UPROPERTY(EditAnywhere)
	int32 PoisonDefend;
	UPROPERTY(EditAnywhere)
	int32 DeathDefend;
	UPROPERTY(EditAnywhere)
	int32 ImpactDefend;
	UPROPERTY(EditAnywhere)
	float ToughnessDefend;
	UPROPERTY(EditAnywhere)
	EArmorType ArmorType;
	UPROPERTY(EditAnywhere)
	float Weight;
};

USTRUCT()
struct FTalismanInfo : public FItemInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FText TalismanEffect;
	
};


UCLASS()
class FAKEER_API UERSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void Test();
	
	
protected:

	UPROPERTY()
	class UDataTable* ItemDataTable;
	UPROPERTY()
	class UDataTable* WeaponDataTable;
	UPROPERTY()
	class UDataTable* BattleAshTable;
	UPROPERTY()
	class UDataTable* SpellDataTable;

	TMap<int32 , FItemInfo* > ItemsMap;
	
public:
	FItemInfo* GetItemInfo(int32 ID);
	void ChangeItemEquip(int32);
	void UpdateAdditionAttack();
};

