// Copyright Rob Wilson 2019

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Set door instance to owner
	Owner = GetOwner();

	// Get player pawn
	ActorThatTriggers = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::SetDoorAngle(float Angle)
{
	// Sets door open angle (yaw)
	Owner->SetActorRotation(FRotator(0.0f, Angle, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float CurrentUptime = GetWorld()->GetTimeSeconds();

	// Poll the trigger volume
	// If the actor that triggers is in the volume, then open the door
	if (PressurePlate->IsOverlappingActor(ActorThatTriggers))
	{
		SetDoorAngle(OpenAngle);
		LastDoorOpenTime = CurrentUptime;
	}

	// Check if time to close door
	if (CurrentUptime - LastDoorOpenTime > DoorCloseDelay)
	{
		SetDoorAngle(CloseAngle);
	}
}

