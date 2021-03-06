// Copyright Rob Wilson 2019

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
//#include "Components/InputComponent.h"

#define OUT

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

	UE_LOG(LogTemp, Log, TEXT("[Grabber] Ready"))

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (PhysicsHandle && InputComponent)
	{
		InputComponent->BindAction("Pickup", IE_Pressed, this, &UGrabber::Pickup);
	}

	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("[Grabber] Unable to find 'PhysicsHandleComponent' on %s"), *GetOwner()->GetName())
	}
	
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("[Grabber] Unable to find 'InputComponent' on %s"), *GetOwner()->GetName())
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point
	FVector PlayerLocation; // Will be changed by GetPlayerViewPoint
	FRotator PlayerRotation; // Will be changed by GetPlayerViewPoint

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation,
		OUT PlayerRotation
	);

	FVector LineTraceEnd = PlayerLocation + (PlayerRotation.Vector() * Reach);

	// DEBUG: View red trace
	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0,
		10.0f
	);

	// Setup query params
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	// Ray-cast (Line-Trace) out to reach distance
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);


	// See what we hit
	AActor* ActorHit = LineTraceHit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Log, TEXT("[Grabber] Ray cast hit: %s"), *(ActorHit->GetName()))
	}
}

void UGrabber::Pickup()
{
	UE_LOG(LogTemp, Log, TEXT("[Grabber] PICKUP"))
}

