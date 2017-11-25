// Copyright David Ruiz Vallejo 2017

#include "MyProject.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	doorRotation = FRotator(0.0f, -90.0f, 0.0f);
	rotationLerp = 0.0f;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	_opened = false;
	Super::BeginPlay();
	openerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	rotationLerp += DeltaTime;
	rotationLerp = FMath::Clamp(rotationLerp, 0.0f, 1.0f);

	if (rotationLerp >= 0.0f && rotationLerp < 1.0f)
	{
		_opened = false;
		rotationLerp += DeltaTime;
		GetOwner()->SetActorRotation(doorRotation * rotationLerp);
	}
	else if (rotationLerp >= 1.0f)
	{
		GetOwner()->SetActorRotation(doorRotation);
		_opened = true;
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (triggerVolume->IsOverlappingActor(openerPawn))
	{
		if(!_opened)
			OpenDoor(DeltaTime);
	}
	else {
		OpenDoor(-DeltaTime);
	}
}

