// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/UseItemActorBall.h"

#include "Characters/ERCharacterBase.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Subsystem/ERSubsystem.h"

void AUseItemActorBall::OnItemUsed(int32 ID)
{
	Super::OnItemUsed(ID);
	if (bIsLeaveMaster)
	{
		return;
	}
	if (ItemID == ID)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		//UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(),ProjectileMovementComponent->Velocity,GetActorLocation(),GetActorLocation() + GetActorForwardVector() * 1000);
		ProjectileMovementComponent->Velocity = MyMaster->GetActorForwardVector() * 1000;
		ProjectileMovementComponent->ProjectileGravityScale = 0.5;
		ProjectileMovementComponent->InitialSpeed = 1000;
		ProjectileMovementComponent->SetActive(true);
		bShouldDelete = false;
		bIsLeaveMaster = true;
	}
}

void AUseItemActorBall::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == MyMaster)
	{
		return;
	}
	if (FItemInfo* ItemInfo = GetWorld()->GetGameInstance()->GetSubsystem<UERSubsystem>()->GetItemInfo(ItemID))
	{
		FUseableItem* UseItem = reinterpret_cast<FUseableItem*>(ItemInfo);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),UseItem->ParticleSystem,GetActorLocation());
		if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(OtherActor))
		{
			FPointDamageEvent PointDamageEvent;
			CharacterBase->TakeDamage(0, PointDamageEvent,MyMaster->GetController(),this);
		}
		Destroy();
	}
}


