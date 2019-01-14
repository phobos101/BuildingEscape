// Copyright Rob Wilson 2019

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void SetDoorAngle(float);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
		float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
		float CloseAngle = 0.0f;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate;

	AActor *Owner; // The door object itself
	AActor *ActorThatTriggers; // Actors that can trigger door trigger volumes

	float LastDoorOpenTime;
};	
