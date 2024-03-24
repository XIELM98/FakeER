// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/KnightAnimInstance.h"

#include "Actors/WeaponActor.h"
#include "Characters/ERCharacterBase.h"
#include "Components/PackageComponent.h"
#include "GameFramework/PawnMovementComponent.h"

void UKnightAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(GetOwningActor()))
	{
		Speed = CharacterBase->GetMovementComponent()->Velocity.Length();
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
						const FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo);
						WeaponType = WeaponInfo->WeaponType;
					}
				}
				if (CharacterBase->GetPackageComponent()->GetLeftWeapon())
				{
					if (bIsBothHand)
					{
						FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(CharacterBase->GetPackageComponent()->GetLeftWeapon()->GetID());
						const FWeaponInfo* WeaponInfo = reinterpret_cast<FWeaponInfo*>(ItemInfo);
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
