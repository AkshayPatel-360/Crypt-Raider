// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "ComponentUtils.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMover::SetShouldMove(bool ShouldMoveBool)
{
	ShouldMove = ShouldMoveBool;
}

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	
	Owner = GetOwner();
	OrigionalLocation = Owner->GetActorLocation();
	
	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector TargetLocation = OrigionalLocation ;
	if (ShouldMove)
	{
		TargetLocation = OrigionalLocation + MoveOffset;
	}

	FVector CurrentLocation = Owner->GetActorLocation();
	
	float Speed = MoveOffset.Length() / MoveTime;

	FVector NewLocation = 	FMath::VInterpConstantTo(CurrentLocation,TargetLocation,DeltaTime,Speed);
	Owner->SetActorLocation( NewLocation);
	
	
}

