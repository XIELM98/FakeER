// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "WeaponActor.generated.h"

USTRUCT()
struct FWeaponPanel
{
	GENERATED_BODY()

	
};

UCLASS()
class FAKEER_API AWeaponActor : public AItemActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* WeaponCapsuleComponent;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY()
	class AERCharacterBase* MyMaster;


	bool bIsDamageEnable;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetupMasterAndID(AERCharacterBase* Master,int32 ID);
	UCapsuleComponent* GetCapsuleComponent() const {return WeaponCapsuleComponent;}
	void SetDamageEnable(bool NewEnable) {bIsDamageEnable = NewEnable;}
	AERCharacterBase* GetMaster() const {return MyMaster;}
	
public:
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> RightHandLightAttack;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> RightHandHeavyAttack;

	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> BothHandLightAttack;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> BothHandHeavyAttack;
	
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> LeftHandLightAttack;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* Guard;
	UPROPERTY(EditAnywhere)
	UAnimMontage* RunAttack;
	UPROPERTY(EditAnywhere)
	UAnimMontage* RollAttack;
	UPROPERTY(EditAnywhere)
	UAnimMontage* DodgeAttack;
	
	
};



