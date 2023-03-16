// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#include <string>



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent *PhysicsHandle = GetUPhysicsHandleComponent();
	
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector HoldLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(HoldLocation,GetComponentRotation());
	}
	
}

void UGrabber::GrabObject()
{

	UPhysicsHandleComponent *PhysicsHandle = GetUPhysicsHandleComponent();

	if (PhysicsHandle == nullptr)
	{
		return;
	}
	FVector Start = GetComponentLocation() ;
	FVector End = Start  + GetForwardVector() * MaxGrabDistance;
	DrawDebugSphere(GetWorld(),End,10,10,FColor::Blue,false,5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius) ;
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult,Start,End,FQuat::Identity,ECC_GameTraceChannel2,Sphere);

	//DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10,10,FColor::Blue,false,5);
	if (HasHit)
	{
			UPrimitiveComponent* HitComponent = HitResult.GetComponent();
			HitComponent->WakeAllRigidBodies();
			HitResult.GetActor()->Tags.Add("Grabbed");
			PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation());
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp,Display,TEXT("Relese called "));

	UPhysicsHandleComponent *PhysicsHandle = GetUPhysicsHandleComponent();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeRigidBody();
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
	
	
}


UPhysicsHandleComponent* UGrabber::GetUPhysicsHandleComponent() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (Result == nullptr)
	{
		UE_LOG(LogTemp,Display,TEXT("Grabber require UPhysicsHandleComponent"));
	}
	return  Result;
}
