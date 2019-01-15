// Copyright Rob Wilson 2019

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

	UE_LOG(LogTemp, Warning, TEXT("[Grabber] ready"))	
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

	// DEBUG: View red trace
	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		PlayerLocation + (PlayerRotation.Vector() * Reach),
		FColor(255, 0, 0),
		false,
		0.0f,
		0,
		10.0f
	);

	// Ray-cast out to reach distance

	// See what we hit
}

