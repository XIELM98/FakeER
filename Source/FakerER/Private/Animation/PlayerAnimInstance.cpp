// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerAnimInstance.h"


#include "ERHUD.h"
#include "Actors/UseItemActor.h"
#include "Actors/WeaponActor.h"
#include "Characters/ERCharacterBase.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/ERMovementComponent.h"
#include "Components/PackageComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MainUserWidget.h"
#include "UI/Widgets/EquipmentWidget.h"
#include "Subsystem/ERSubsystem.h"


void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(GetOwningActor()))
	{
		bIsRoll = CharacterBase->GetIsRoll();
		Speed = CharacterBase->GetMovementComponent()->Velocity.Length();
		InputX = CharacterBase->GetInputX();
		InputY = CharacterBase->GetInputY();
		bIsLock = CharacterBase->GetIsLock();
		bIsBothHand = CharacterBase->GetIsBothHand();

		if (CharacterBase->GetPackageComponent())
		{
			if (CharacterBase->GetPackageComponent()->GetRightWeapon() || CharacterBase->GetPackageComponent()->GetLeftWeapon())
			{
				bIsHoldWeapon = true;
				if (CharacterBase->GetPackageComponent()->GetRightWeapon())
				{
					if (bIsBothHand)
					{
						FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(CharacterBase->GetPackageComponent()->GetRightWeapon()->GetID());
						FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo);
						WeaponType = WeaponInfo->WeaponType;
					}
				}
				if (CharacterBase->GetPackageComponent()->GetLeftWeapon())
				{
					if (bIsBothHand)
					{
						FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(CharacterBase->GetPackageComponent()->GetLeftWeapon()->GetID());
						FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo);
						WeaponType = WeaponInfo->WeaponType;
					}
				}
			}
			else
			{
				bIsHoldWeapon = false;
			}
		}
	}
		
}

void UPlayerAnimInstance::AnimNotify_StartDamage()
{

	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(GetOwningActor()))
	{
		if (CharacterBase->GetCharacterState() == ECharacterState::LeftAttack)
		{
			if (AWeaponActor* Weapon = CharacterBase->GetPackageComponent()->GetLeftWeapon())
			{
				Weapon->SetDamageEnable(true);
				Weapon->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			}
		}
		else if (CharacterBase->GetCharacterState() == ECharacterState::RightAttack)
		{
			if (AWeaponActor* Weapon = CharacterBase->GetPackageComponent()->GetRightWeapon())
			{
				Weapon->SetDamageEnable(true);
				Weapon->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			}
		}
		
		if (CharacterBase->GetMovementComponent())
		{
			if (UERMovementComponent* MovementComponent = Cast<UERMovementComponent>(CharacterBase->GetMovementComponent()))
			{
				MovementComponent->CanAttackRotate();
			}
		}
		
	}
}

void UPlayerAnimInstance::AnimNotify_EndDamage()
{
	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(GetOwningActor()))
	{
		if (CharacterBase->GetCharacterState() == ECharacterState::LeftAttack)
		{
			if (AWeaponActor* Weapon = CharacterBase->GetPackageComponent()->GetLeftWeapon())
			{
				Weapon->SetDamageEnable(false);
				Weapon->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
		else if (CharacterBase->GetCharacterState() == ECharacterState::RightAttack)
		{
			if (AWeaponActor* Weapon = CharacterBase->GetPackageComponent()->GetRightWeapon())
			{
				Weapon->SetDamageEnable(false);
				Weapon->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
		if (CharacterBase->GetMovementComponent())
		{
			if (UERMovementComponent* MovementComponent = Cast<UERMovementComponent>(CharacterBase->GetMovementComponent()))
			{
				MovementComponent->CanNotAttackRotate();
			}
		}
		CharacterBase->SetCharacterState(ECharacterState::Normal);
		CharacterBase->AddAttackIndex();
	}
}

void UPlayerAnimInstance::AnimNotify_FinishRoll()
{
	if(AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
	{
		CharacterBase->SetCharacterState(ECharacterState::Normal);
		CharacterBase->FinishRoll();
	}
}

void UPlayerAnimInstance::AnimNotify_EndAttack()
{
	if(AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
	{
		CharacterBase->SetCharacterState(ECharacterState::Normal);
		CharacterBase->ClearAttackIndex();
		CharacterBase->StartAddEndurance();
	}
}

void UPlayerAnimInstance::AnimNotify_ContinueAttack()
{
	if(AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
	{
		CharacterBase->SetCharacterState(ECharacterState::Normal);
		CharacterBase->AddAttackIndex();
	}
}

void UPlayerAnimInstance::AnimNotify_UnEquipRight()
{
	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
	{
		if (CharacterBase->GetPackageComponent()->GetRightWeapon())
		{
			if(CharacterBase->GetPackageComponent()->OnUnEquipRightWeapon.IsBound())
			{
				CharacterBase->GetPackageComponent()->OnUnEquipRightWeapon.Broadcast();
			}
		}

		CharacterBase->PlayAnimMontage(CharacterBase->GetEquipRightAnim(),1,TEXT("Equip"));
	}
}

void UPlayerAnimInstance::AnimNotify_EquipRight()
{
	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
	{
		if (CharacterBase->GetPackageComponent())
		{
			if(CharacterBase->GetPackageComponent()->OnEquipRightWeapon.IsBound())
			{
				CharacterBase->GetPackageComponent()->OnEquipRightWeapon.Broadcast();
			}
		}
	}
}

void UPlayerAnimInstance::AnimNotify_UnEquipLeft()
{
	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
	{
		if (CharacterBase->GetPackageComponent()->GetLeftWeapon())
		{
			if(CharacterBase->GetPackageComponent()->OnUnEquipLeftWeapon.IsBound())
			{
				CharacterBase->GetPackageComponent()->OnUnEquipLeftWeapon.Broadcast();
			}
		}
		if (CharacterBase->bShouldEquip)
		{
			CharacterBase->PlayAnimMontage(CharacterBase->GetEquipLeftAnim(),1,TEXT("Equip"));
		}
		else
		{
			CharacterBase->bShouldEquip = true;
			CharacterBase->SetIsBothHand(true);
		}
	}
}

void UPlayerAnimInstance::AnimNotify_EquipLeft()
{
	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
	{
		if (CharacterBase->GetPackageComponent())
		{
			if(CharacterBase->GetPackageComponent()->OnEquipLeftWeapon.IsBound())
			{
				CharacterBase->GetPackageComponent()->OnEquipLeftWeapon.Broadcast();
			}
		}
	}
}

void UPlayerAnimInstance::AnimNotify_StartUseItem()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if (HUD->GetMainUserWidget()->GetEquipmentWidget()->GetEquipItem() != -1)
		{
			if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
			{
				if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(HUD->GetMainUserWidget()->GetEquipmentWidget()->GetEquipItem()))
				{
					FUseableItem* UseItem = reinterpret_cast<FUseableItem*>(ItemInfo);
					AUseItemActor* UseItemActor = GetWorld()->SpawnActor<AUseItemActor>(UseItem->UseItemClass);
					UseItemActor->SetupMasterAndID(CharacterBase,HUD->GetMainUserWidget()->GetEquipmentWidget()->GetEquipItem());
					UseItemActor->AttachToComponent(CharacterBase->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("UseItem"));
					if (CharacterBase->GetPackageComponent() && CharacterBase->GetPackageComponent()->GetRightWeapon())
					{
						CharacterBase->GetPackageComponent()->GetRightWeapon()->SetActorHiddenInGame(true);
					}
					CharacterBase->GetPackageComponent()->SetUseItem(UseItemActor);
				}
			}
		}
	}
}

void UPlayerAnimInstance::AnimNotify_EndUseItem()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if (HUD->GetMainUserWidget()->GetEquipmentWidget()->GetEquipItem() != -1)
		{
			if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
			{
				if (CharacterBase->GetPackageComponent() && CharacterBase->GetPackageComponent()->GetRightWeapon())
				{
					CharacterBase->GetPackageComponent()->GetRightWeapon()->SetActorHiddenInGame(false);
				}
				if (CharacterBase->GetPackageComponent()->GetUseItem() && CharacterBase->GetPackageComponent()->GetUseItem()->GetShouldDelete())
				{
					CharacterBase->GetPackageComponent()->DeleteUseItem();
				}
			}
		}
	}
}

void UPlayerAnimInstance::AnimNotify_UseItem()
{
	if (AERHUD* HUD = Cast<AERHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD()))
	{
		if (HUD->GetMainUserWidget()->GetEquipmentWidget()->GetEquipItem() != -1)
		{
			if (AERPlayerCharacter* PlayerCharacter = Cast<AERPlayerCharacter>(TryGetPawnOwner()))
			{
				if (PlayerCharacter->GetPackageComponent()->OnUseItem.IsBound())
				{
					PlayerCharacter->GetPackageComponent()->OnUseItem.Broadcast(HUD->GetMainUserWidget()->GetEquipmentWidget()->GetEquipItem());
				}
			}
		}
	}
}

void UPlayerAnimInstance::AnimNotify_CanAttackRotate()
{
	if (bIsLock)
	{
		return;
	}
	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
	{
		if (CharacterBase->GetMovementComponent())
		{
			if (UERMovementComponent* MovementComponent = Cast<UERMovementComponent>(CharacterBase->GetMovementComponent()))
			{
				MovementComponent->CanAttackRotate();
			}
		}
	}
}

void UPlayerAnimInstance::AnimNotify_CannotAttackRotate()
{
	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(TryGetPawnOwner()))
	{
		if (CharacterBase->GetMovementComponent())
		{
			if (UERMovementComponent* MovementComponent = Cast<UERMovementComponent>(CharacterBase->GetMovementComponent()))
			{
				MovementComponent->CanNotAttackRotate();
			}
		}
	}
}
