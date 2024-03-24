// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ERMovementComponent.h"


// Sets default values for this component's properties
UERMovementComponent::UERMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UERMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UERMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UERMovementComponent::SetMaxWalkSpeed(float Speed)
{
	MaxWalkSpeed = Speed;
}

