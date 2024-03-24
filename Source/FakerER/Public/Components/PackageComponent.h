// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PackageComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(DelegateEquipItem,int32)
DECLARE_TS_MULTICAST_DELEGATE(DelegateChangeEquipment)
DECLARE_MULTICAST_DELEGATE_OneParam(DelegateUseItem,int32)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FAKEER_API UPackageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPackageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void OnEquipItem(int32);
    void OnUnEquipItem(int32);

	void UpdateRightWeapon();
	void UpdateLeftWeapon();
	void UpdateItem();
	void UpdateArmor(int32 ID, bool IsEquip);
	void UpdateTalisman(int32 ID, bool IsEquip);

	void UpdateCharacterPanel(int32 ID,bool IsEquip,bool IsRight);

	void ItemUsed(int32 ID);
	
	
protected:
	UPROPERTY()
	class AWeaponActor* LeftHoldWeapon;
	UPROPERTY()
	AWeaponActor* RightHoldWeapon;
	UPROPERTY()
	class AUseItemActor* UseItemActor;
	
	TMap<int32 ,int32 >AllItemMap;
	TMap<int32 ,int32 >EquipRightWeaponMap;
	TMap<int32 ,int32 >EquipLeftWeaponMap;
	TMap<int32 ,int32 >EquipItemMap;

	UPROPERTY(EditAnywhere)
	TMap<int32, int32> PreItemMap;
	TMap<int32, int32> TempItemMap;
	
public:
	void AddItemToPackage(int32 InID,int32 Num = 1);
	TMap<int32, int32> GetItemMap() const {return AllItemMap;}

	TMap<int32 ,int32 > GetEquipRightWeaponMap() const {return EquipRightWeaponMap;}
	TMap<int32 ,int32 > GetEquipLeftWeaponMap() const {return EquipLeftWeaponMap;}
	TMap<int32 ,int32 > GetEquipItemMap() const {return EquipItemMap;}
	
	int32 GetItemNum(int32 ID);
	
	void EquipRightWeapon(int32 ID);
	void EquipLeftWeapon(int32 ID);

	AWeaponActor* GetLeftWeapon() const {return LeftHoldWeapon;}
	AWeaponActor* GetRightWeapon() const {return RightHoldWeapon;}
	void SetUseItem(AUseItemActor* NewUseItem) {UseItemActor = NewUseItem;}
	AUseItemActor* GetUseItem() const {return  UseItemActor;}
	void DeleteUseItem();

	void ClearItem();
	
public:
	DelegateEquipItem OnEquipFromPackage;
	DelegateEquipItem OnUnEquipFromPackage;
	
	DelegateChangeEquipment OnChangeItem;
	DelegateChangeEquipment OnChangeSpell;
	DelegateChangeEquipment OnChangeLeftWeapon;
	DelegateChangeEquipment OnChangeRightWeapon;
	DelegateChangeEquipment OnUnEquipLeftWeapon;
	DelegateChangeEquipment OnUnEquipRightWeapon;
	DelegateChangeEquipment OnEquipLeftWeapon;
	DelegateChangeEquipment OnEquipRightWeapon;
	
	DelegateUseItem OnUseItem;
};



