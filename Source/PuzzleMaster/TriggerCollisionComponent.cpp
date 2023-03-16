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


	//UE_LOG(LogTemp,Display,TEXT("Unlocking "));
	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		UE_LOG(LogTemp,Display,TEXT("Unlocking "));

		Mover->SetShouldMove(true);
	}
	else
	{
		UE_LOG(LogTemp,Display,TEXT("Relockking "));

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
		if (Actor->ActorHasTag(AcceptableActorTagName))
		{
			return Actor;
		}
	}
	return nullptr;
}
