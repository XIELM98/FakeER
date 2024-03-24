// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/UseItemActorKnife.h"

#include "Characters/ERCharacterBase.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"


void AUseItemActorKnife::OnItemUsed(int32 ID)
{
	Super::OnItemUsed(ID);
	if (bIsLeaveMaster)
	{
		return;
	}
	if (ItemID == ID)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UE_LOG(LogTemp, Log, TEXT("Used"))
		ProjectileMovementComponent->InitialSpeed = 1000;
		ProjectileMovementComponent->Velocity = MyMaster->GetActorForwardVector() * 1000;
		ProjectileMovementComponent->SetActive(true);
		
		bShouldDelete = false;
		SetLifeSpan(3.f);
		bIsLeaveMaster = true;
	}
}

void AUseItemActorKnife::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AERCharacterBase* CharacterBase = Cast<AERCharacterBase>(OtherActor))
	{
		if (!MyMaster)
		{
			return;
		}
		if (CharacterBase == MyMaster)
		{
			return;
		}
		FPointDamageEvent PointDamageEvent;
		PointDamageEvent.HitInfo = SweepResult;
		CharacterBase->TakeDamage(0,PointDamageEvent,MyMaster->GetController(),this);
		ProjectileMovementComponent->SetActive(false);
		//UE_LOG(LogTemp, Log, TEXT("%d %d %d"),SweepResult.Location.X,SweepResult.Location.Y,SweepResult.Location.Z)
		//AttachToComponent(CharacterBase->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,SweepResult.BoneName);
		SetLifeSpan(30.f);
	}
}


