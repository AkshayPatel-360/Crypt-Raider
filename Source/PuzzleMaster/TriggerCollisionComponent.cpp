// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerCollisionComponent.h"

// Sets default values for this component's properties
UTriggerCollisionComponent::UTriggerCollisionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UTriggerCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		Mover->SetShouldMove(true);
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerCollisionComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerCollisionComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (AActor* Actor : Actors)
	{
		const bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTagName);
		const bool HasGrabbed = Actor->ActorHasTag("Grabbed");
		
		if ( HasAcceptableTag && !HasGrabbed)
		{
			return Actor;
		}
	}
	return nullptr;
}
