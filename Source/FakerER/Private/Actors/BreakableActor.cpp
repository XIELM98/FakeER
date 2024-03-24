// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BreakableActor.h"

#include "GeometryCollection/GeometryCollectionComponent.h"
//#include "Chaos/ChaosGameplayEventDispatcher.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABreakableActor::ABreakableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GeometryCollectionComponent = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometrtCollection"));
	SetRootComponent(GeometryCollectionComponent);
	GeometryCollectionComponent->SetGenerateOverlapEvents(true);
	GeometryCollectionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	
	
}


// Called when the game starts or when spawned
void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();

	GeometryCollectionComponent->OnChaosBreakEvent.AddDynamic(this,&ABreakableActor::OnBreak);
	
}

void ABreakableActor::OnBreak(const FChaosBreakEvent& BreakEvent)
{
	if (BreakSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,BreakSound,BreakEvent.Location,GetActorRotation());
		
	}
}

// Called every frame
void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

