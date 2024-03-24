// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ERCharacterBase.h"


#include "ERHUD.h"
#include "Actors/WeaponActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/ERMovementComponent.h"
#include "Components/PackageComponent.h"
#include "DSP/WaveTableOsc.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Subsystem/ERSubsystem.h"
#include "UI/MainUserWidget.h"
#include "UI/Widgets/EquipmentWidget.h"

// Sets default values
AERCharacterBase::AERCharacterBase(const FObjectInitializer& Initializer)
	:Super(Initializer.SetDefaultSubobjectClass<UERMovementComponent>(CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PackageComponent = CreateDefaultSubobject<UPackageComponent>(TEXT("PackageComp"));
	ERMovementComponent = Cast<UERMovementComponent>(GetCharacterMovement());

	LockTag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockTag"));
	LockTag->SetupAttachment(RootComponent);
	LockTag->SetVisibility(false);
	LockTag->SetRelativeLocation(FVector(0, 0, 80.f));
	LockTag->SetRelativeRotation(FRotator(0.f, 180.f , 180.f ));
	UStaticMesh* Cone = LoadObject<UStaticMesh>(this, TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	LockTag->SetStaticMesh(Cone);
	LockTag->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
	LockTag->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	
	bCanAddEndurance = true;
	AddEnduranceSpeed = 1.0f;
	RollEndurance = 20.f;
	bShouldEquip = true;
	WalkSpeed = 400.f;
	RunSpeed = 600.f;
	bCanExecute = true;
	ERMovementComponent->SetMaxWalkSpeed(WalkSpeed);
}

// Called when the game starts or when spawned
void AERCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
	
	InitPlayerPanel();
	
	HitAnim = LoadObject<UAnimMontage>(this,TEXT(""));
	Drink = LoadObject<UAnimMontage>(this,TEXT("/Script/Engine.AnimMontage'/Game/FakeER/Animation/Normal/AM_Drink.AM_Drink'"));
	PickUp = LoadObject<UAnimMontage>(this,TEXT(""));
	EquipLeft = LoadObject<UAnimMontage>(this,TEXT("/Script/Engine.AnimMontage'/Game/FakeER/Animation/Normal/AM_LeftEquip.AM_LeftEquip'"));
	UnEquipLeft = LoadObject<UAnimMontage>(this,TEXT("/Script/Engine.AnimMontage'/Game/FakeER/Animation/Normal/AM_LeftUnEquip.AM_LeftUnEquip'"));
	EquipRight = LoadObject<UAnimMontage>(this,TEXT("/Script/Engine.AnimMontage'/Game/FakeER/Animation/Normal/AM_RightEquip.AM_RightEquip'"));
	UnEquipRight = LoadObject<UAnimMontage>(this,TEXT("/Script/Engine.AnimMontage'/Game/FakeER/Animation/Normal/AM_RightUnEquip.AM_RightUnEquip'"));
	

	if (PackageComponent)
	{
		PackageComponent->OnChangeLeftWeapon.AddUObject(this,&AERCharacterBase::CancelBothHand);
		PackageComponent->OnChangeRightWeapon.AddUObject(this,&AERCharacterBase::CancelBothHand);
	}
	
}


void AERCharacterBase::UseItem()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if (HUD->GetMainUserWidget()->GetEquipmentWidget()->GetEquipItem() != -1)
		{
			FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(HUD->GetMainUserWidget()->GetEquipmentWidget()->GetEquipItem());
			FUseableItem* UseItem = reinterpret_cast<FUseableItem*>(ItemInfo);
			if (PackageComponent)
			{
				if (PackageComponent->GetItemNum(HUD->GetMainUserWidget()->GetEquipmentWidget()->GetEquipItem()) >= 1)
				{
					if (UseItem->UseAnim)
					{
						PlayAnimMontage(UseItem->UseAnim);
						CharacterPanel.NowMana -= UseItem->CostMana; 
					}
				}
			}
		}
	}
}

void AERCharacterBase::Roll()
{
	if (GetCharacterState() == ECharacterState::Normal)
	{
		StopAnimMontage(GetCurrentMontage());
		SetCharacterState(ECharacterState::Roll);
		CostEndurance(RollEndurance);
		bIsRoll = true;
		bCanAddEndurance = false;
	}
}

void AERCharacterBase::Run()
{
	if (CharacterPanel.NowEndurance <= 0)
	{
		OverRun();
		return;
	}
	if (bIsLock)
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	ERMovementComponent->SetMaxWalkSpeed(RunSpeed);
	bCanAddEndurance = false;
	CostEndurance(0.2f);
}

void AERCharacterBase::OverRun()
{
	if (bIsLock)
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		
	}
	ERMovementComponent->SetMaxWalkSpeed(WalkSpeed);
	bCanAddEndurance = true;
}

void AERCharacterBase::RightLightAttack()
{
	if (PackageComponent && PackageComponent->GetRightWeapon())
	{
		if (CurrentState == ECharacterState::Normal)
		{
			if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(PackageComponent->GetRightWeapon()->GetID()))
			{
				if (FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo))
				{
					if (WeaponInfo->WeaponType == EWeaponType::Bell || WeaponInfo->WeaponType == EWeaponType::Staff)
					{
						ReleaseSpell();
						StopAddEndurance();
					}
					else
					{
						if (bIsBothHand)
						{
							if (PackageComponent->GetRightWeapon()->BothHandLightAttack.Num() <= 0)
							{
								return;
							}
							if (AttackIndex >= PackageComponent->GetRightWeapon()->BothHandLightAttack.Num())
							{
								AttackIndex = 0;
							}
							if (PackageComponent->GetRightWeapon()->BothHandLightAttack[AttackIndex])
							{
								if (CharacterPanel.NowEndurance > 0)
								{
									PlayAnimMontage(PackageComponent->GetRightWeapon()->BothHandLightAttack[AttackIndex]);
									CostEndurance(WeaponInfo->CostEndurance);
									CurrentState = ECharacterState::RightAttack;
									StopAddEndurance();
								}
							}
						}
						else
						{
							if (PackageComponent->GetRightWeapon()->RightHandLightAttack.Num() <= 0)
							{
								return;
							}
							if (AttackIndex >= PackageComponent->GetRightWeapon()->RightHandLightAttack.Num())
							{
								AttackIndex = 0;
							}
							if (PackageComponent->GetRightWeapon()->RightHandLightAttack[AttackIndex])
							{
								if (CharacterPanel.NowEndurance > 0)
								{
									PlayAnimMontage(PackageComponent->GetRightWeapon()->RightHandLightAttack[AttackIndex]);
									CostEndurance(WeaponInfo->CostEndurance);
									CurrentState = ECharacterState::RightAttack;
									StopAddEndurance();
								}
							}
						}
					}
				}
			}
		}
	}
}

void AERCharacterBase::RightHeavyAttack()
{
	if (PackageComponent && PackageComponent->GetRightWeapon())
	{
		if (CurrentState == ECharacterState::Normal)
		{
			if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(PackageComponent->GetRightWeapon()->GetID()))
			{
				if (FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo))
				{
					if (bIsBothHand)
					{
						if (PackageComponent->GetRightWeapon()->BothHandHeavyAttack.Num() <= 0)
						{
							return;
						}
						if (AttackIndex >= PackageComponent->GetRightWeapon()->BothHandHeavyAttack.Num())
						{
							AttackIndex = 0;
						}
						if (CharacterPanel.NowEndurance > 0)
						{
							UE_LOG(LogTemp,Log,TEXT("ChargeOver"))
							PlayAnimMontage(PackageComponent->GetRightWeapon()->BothHandHeavyAttack[AttackIndex], 1.f, TEXT("ChargeOver"));
							CostEndurance(WeaponInfo->CostEndurance);
							CurrentState = ECharacterState::RightAttack;
							StopAddEndurance();
						}
					}
					else
					{
						if (PackageComponent->GetRightWeapon()->RightHandHeavyAttack.Num() <= 0)
						{
							return;
						}
						if (AttackIndex >= PackageComponent->GetRightWeapon()->RightHandHeavyAttack.Num())
						{
							AttackIndex = 0;
						}
						if (CharacterPanel.NowEndurance > 0)
						{
							PlayAnimMontage(PackageComponent->GetRightWeapon()->RightHandHeavyAttack[AttackIndex], 1.f, TEXT("ChargeOver"));
							CostEndurance(WeaponInfo->CostEndurance);
							CurrentState = ECharacterState::RightAttack;
							StopAddEndurance();
						}
					}
				}
			}
		}
	}	
}



void AERCharacterBase::ChargeAttack()
{
	if (PackageComponent && PackageComponent->GetRightWeapon())
	{
		if (CurrentState == ECharacterState::Normal)
		{
			if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(PackageComponent->GetRightWeapon()->GetID()))
			{
				if (FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo))
				{
					if (bIsBothHand)
					{
						if (PackageComponent->GetRightWeapon()->BothHandHeavyAttack.Num() <= 0)
						{
							return;
						}
						if (AttackIndex >= PackageComponent->GetRightWeapon()->BothHandHeavyAttack.Num())
						{
							AttackIndex = 0;
						}
						if (CharacterPanel.NowEndurance > 0)
						{
							PlayAnimMontage(PackageComponent->GetRightWeapon()->BothHandHeavyAttack[AttackIndex]);
							CostEndurance(WeaponInfo->CostEndurance * 2.0f);
							CurrentState = ECharacterState::RightAttack;
							StopAddEndurance();
						}
					}
					else
					{
						if (PackageComponent->GetRightWeapon()->RightHandHeavyAttack.Num() <= 0)
						{
							return;
						}
						if (AttackIndex >= PackageComponent->GetRightWeapon()->RightHandHeavyAttack.Num())
						{
							AttackIndex = 0;
						}
						if (CharacterPanel.NowEndurance > 0)
						{
							PlayAnimMontage(PackageComponent->GetRightWeapon()->RightHandHeavyAttack[AttackIndex]);
							CostEndurance(WeaponInfo->CostEndurance * 2.0f);
							CurrentState = ECharacterState::RightAttack;
							StopAddEndurance();
						}
					}
				}
			}
		}
	}	
}

void AERCharacterBase::LeftLightAttack()
{
	if (PackageComponent && PackageComponent->GetLeftWeapon())
	{
		if (CurrentState == ECharacterState::Normal)
		{
			if (bIsBothHand)
			{
				if (PackageComponent->GetLeftWeapon()->Guard)
				{
					PlayAnimMontage(PackageComponent->GetLeftWeapon()->Guard);
				}
				if (PackageComponent->GetRightWeapon()->Guard)
				{
					PlayAnimMontage(PackageComponent->GetRightWeapon()->Guard);
				}
				CurrentState = ECharacterState::Guard;
			}
			else
			{
				if (PackageComponent->GetLeftWeapon()->LeftHandLightAttack.Num() <= 0)
				{
					return;
				}
				if (AttackIndex >= PackageComponent->GetLeftWeapon()->LeftHandLightAttack.Num())
				{
					AttackIndex = 0;
				}
				if (CharacterPanel.NowEndurance > 0)
				{
					if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(PackageComponent->GetLeftWeapon()->GetID()))
					{
						if (FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo))
						{
							PlayAnimMontage(PackageComponent->GetLeftWeapon()->LeftHandLightAttack[AttackIndex]);
							CostEndurance(WeaponInfo->CostEndurance);
							CurrentState = ECharacterState::RightAttack;
							StopAddEndurance();
						}
					}
				}
			}
		}
	}
}

void AERCharacterBase::Guard()
{
	UE_LOG(LogTemp,Log,TEXT("Guard"))
}

void AERCharacterBase::BattleArt()
{
	UE_LOG(LogTemp, Log, TEXT("BattleArt"))
}



void AERCharacterBase::DoJump()
{
	Jump();
}

void AERCharacterBase::ChangeSpell()
{
	if(PackageComponent)
	{
		if(PackageComponent->OnChangeSpell.IsBound())
		{
			PackageComponent->OnChangeSpell.Broadcast();
		}
	}
}

void AERCharacterBase::ChangeItem()
{
	if(PackageComponent)
	{
		if(PackageComponent->OnChangeItem.IsBound())
		{
			PackageComponent->OnChangeItem.Broadcast();
		}
	}
}

void AERCharacterBase::ChangeLeftWeapon()
{
	if(PackageComponent)
	{
		if(PackageComponent && PackageComponent->OnChangeLeftWeapon.IsBound())
		{
			PackageComponent->OnChangeLeftWeapon.Broadcast();
			PlayAnimMontage(UnEquipLeft);
		}
	}
}

void AERCharacterBase::ChangeRightWeapon()
{
	if (PackageComponent && PackageComponent->OnChangeRightWeapon.IsBound())
	{
		PackageComponent->OnChangeRightWeapon.Broadcast();
		PlayAnimMontage(UnEquipRight);
	}
}

void AERCharacterBase::RightBothHand()
{
	if (PackageComponent)
	{
		if (!PackageComponent->GetRightWeapon())
		{
			return;
		}
		if (bIsBothHand)
		{
			CancelBothHand();
		}
		else
		{
			if (PackageComponent->GetLeftWeapon())
			{
				bShouldEquip = false;
				PlayAnimMontage(UnEquipLeft);
			}
			else
			{
				bIsBothHand = true;
			}
			PackageComponent->GetRightWeapon()->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("SwordBothHand"));
		}
	}
}

void AERCharacterBase::LeftBothHand()
{
	if (!PackageComponent->GetLeftWeapon())
	{
		return;
	}
	if (PackageComponent)
	{
		if (PackageComponent->GetRightWeapon())
		{
			bShouldEquip = false;
			PlayAnimMontage(UnEquipRight);
		}
		else
		{
			bIsBothHand = true;
		}
		PackageComponent->GetRightWeapon()->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("SwordBothHand"));
	}
}

void AERCharacterBase::ReleaseSpell()
{
	
}

void AERCharacterBase::InitPlayerPanel()
{
	CharacterPanel.MaxHP = 500.f;
	CharacterPanel.NowHP = CharacterPanel.MaxHP;
	CharacterPanel.MaxMana = 100.f;
	CharacterPanel.NowMana = CharacterPanel.MaxMana;
	CharacterPanel.MaxEndurance = 100.f;
	CharacterPanel.NowEndurance = CharacterPanel.MaxEndurance;
	CharacterPanel.MaxEquipWeight = 50.f;
	CharacterPanel.NowEquipWeight = 10.f;
	CharacterPanel.MemorySpace = 2;
	
	CharacterPanel.LeftPhysicalAttack = CharacterAttribute.Level;
	CharacterPanel.LeftFireAttack = 0;
	CharacterPanel.LeftMagicAttack = 0;
	CharacterPanel.LeftLightingAttack = 0;
	CharacterPanel.RightPhysicalAttack = CharacterAttribute.Level;
	CharacterPanel.RightFireAttack = 0;
	CharacterPanel.RightMagicAttack = 0;
	CharacterPanel.RightLightingAttack = 0;
	
	CharacterPanel.MaxToughness = 10.f;
	CharacterPanel.NowToughness = CharacterPanel.MaxToughness;
	CharacterPanel.PhysicalDefend = CharacterAttribute.Level;
	CharacterPanel.FireDefend = CharacterAttribute.Level;
	CharacterPanel.MagicDefend = CharacterAttribute.Level;
	CharacterPanel.LightingDefend = CharacterAttribute.Level;
	CharacterPanel.BloodingDefend = 100.f;
	CharacterPanel.PoisonDefend = 100.f;
	CharacterPanel.DeathDefend = 100.f;
}

void AERCharacterBase::CancelBothHand()
{
	if (!bIsBothHand)
	{
		return;
	}
	if (PackageComponent->GetRightWeapon())
	{
		PlayAnimMontage(UnEquipLeft);
		PackageComponent->GetRightWeapon()->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("RightWeapon"));
	}
	else if (PackageComponent->GetLeftWeapon())
	{
		PlayAnimMontage(UnEquipRight);
		PackageComponent->GetLeftWeapon()->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("LeftWeapon"));
	}
	bIsBothHand = false;
}

void AERCharacterBase::CostEndurance(float InEndurance)
{
	if (CharacterPanel.NowEndurance > 0)
	{
		CharacterPanel.NowEndurance = FMath::Clamp(CharacterPanel.NowEndurance - InEndurance,0,CharacterPanel.NowEndurance);
	}
}

void AERCharacterBase::LeaveBattle()
{
	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	GetWorldTimerManager().SetTimer(ToughnessTimerHandle,this,&AERCharacterBase::AddToughness,0.5,true);
}

void AERCharacterBase::AddToughness()
{
	if (CharacterPanel.NowToughness >= CharacterPanel.MaxToughness)
	{
		GetWorldTimerManager().ClearTimer(ToughnessTimerHandle);
	}
	CharacterPanel.NowToughness++;
}



float AERCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                   AActor* DamageCauser)
{
	//武器伤害
	if (AWeaponActor* WeaponActor = Cast<AWeaponActor>(DamageCauser))
	{
		if (AERCharacterBase* DamageCharacter = Cast<AERCharacterBase>(WeaponActor->GetMaster()))
		{
			if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(WeaponActor->GetID()))
			{
				if (const FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo))
				{
					CharacterPanel.NowHP -= FMath::Clamp(WeaponInfo->PhysicalAttack + WeaponInfo->AdditionPhysicalAttack - CharacterPanel.PhysicalDefend,0,CharacterPanel.MaxHP);
					CharacterPanel.NowHP -= FMath::Clamp(WeaponInfo->MagicAttack + WeaponInfo->AdditionMagicAttack - CharacterPanel.MagicDefend,0,CharacterPanel.MaxHP);
					CharacterPanel.NowHP -= FMath::Clamp(WeaponInfo->FireAttack + WeaponInfo->AdditionFireAttack - CharacterPanel.FireDefend,0,CharacterPanel.MaxHP);
					CharacterPanel.NowHP -= FMath::Clamp(WeaponInfo->LightingAttack + WeaponInfo->AdditionLightingAttack - CharacterPanel.LightingDefend,0,CharacterPanel.MaxHP);
					
					CharacterPanel.NowToughness -= WeaponInfo->ToughnessAttack;
					if(CharacterPanel.NowToughness < 0 && HitAnim)
					{
						
					}
					GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle,this,&AERCharacterBase::LeaveBattle,5.f,false);
					
					if (ItemInfo->Impact >= CharacterPanel.ImpactDefend)
					{
						PlayAnimMontage(HitAnim);
						//CharacterPanel.NowToughness = CharacterPanel.MaxToughness;
						
						//const FPointDamageEvent* PointDamageEvent = static_cast<const FPointDamageEvent*>(&DamageEvent);
						//FVector ImpulseDir = PointDamageEvent->HitInfo.Location - 
					}
				}
				
			}
			if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(WeaponActor->GetID()))
			{
				CharacterPanel.NowToughness -= ItemInfo->ToughnessAttack;
				if(CharacterPanel.NowToughness < 0)
				{
					PlayAnimMontage(HitAnim);
					CharacterPanel.NowToughness = CharacterPanel.MaxToughness;
				}
				if (ItemInfo->Impact >= CharacterPanel.ImpactDefend)
				{
					//const FPointDamageEvent* PointDamageEvent = static_cast<const FPointDamageEvent*>(&DamageEvent);
					//FVector ImpulseDir = PointDamageEvent->HitInfo.Location - 
				}
			}
		}
	}

	//道具伤害
	if (AItemActor* ItemActor = Cast<AItemActor>(DamageCauser))
	{
		if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ItemActor->GetID()))
		{
			CharacterPanel.NowHP -= FMath::Clamp(ItemInfo->PhysicalAttack - CharacterPanel.PhysicalDefend,0,CharacterPanel.MaxHP);
			CharacterPanel.NowHP -= FMath::Clamp(ItemInfo->MagicAttack - CharacterPanel.MagicDefend,0,CharacterPanel.MaxHP);
			CharacterPanel.NowHP -= FMath::Clamp(ItemInfo->FireAttack - CharacterPanel.FireDefend,0,CharacterPanel.MaxHP);
			CharacterPanel.NowHP -= FMath::Clamp(ItemInfo->LightingAttack - CharacterPanel.LightingDefend,0,CharacterPanel.MaxHP);
		}
	}
	return 0;
}

void AERCharacterBase::StopMove()
{
	ERMovementComponent->SetMaxWalkSpeed(0);
}

void AERCharacterBase::StartMove()
{
	ERMovementComponent->SetMaxWalkSpeed(WalkSpeed);
}


// Called every frame
void AERCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AERCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

