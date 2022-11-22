// Fill out your copyright notice in the Description page of Project Settings.


#include "ARManager.h"

#include "Components/InputComponent.h"



// Sets default values
AARManager::AARManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	RootComponent = CameraComponent;
	
	
}

// Called when the game starts or when spawned
void AARManager::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* controller = UGameplayStatics::GetPlayerController(this,0);
	int xSize, ySize;
	controller->GetViewportSize(xSize, ySize);
	ScreenSize.X = static_cast<float>(xSize);
	ScreenSize.Y = static_cast<float>(ySize);
	ScreenSize *= 0.5f;
}

// Called every frame
void AARManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!bScanIsComplete)
	{
		
		 Results = UARBlueprintLibrary::LineTraceTrackedObjects(ScreenSize,
			false,false, true, true);
		 if(Results.Num() > 0)
		 {
			 ARCorePlane = static_cast<UARPlaneGeometry*>(Results[0].GetTrackedGeometry());
			 planeTr = ARCorePlane->GetLocalToWorldTransform();
			 bScanIsComplete = true;
		 }
	}
	else
	{
		UARBlueprintLibrary::DebugDrawTrackedGeometry(ARCorePlane, this,
			FColor::Red);
	}
	
}

// Called to bind functionality to input
void AARManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AARManager::InputTouch);

}

void AARManager::InputTouch(ETouchIndex::Type fingerIndex, FVector location)
{
	if(ARCorePlane != nullptr && !bIsSpawned)
	{
		AARLevel* realCurrentLevel = static_cast<AARLevel*>(currentLevel.GetDefaultObject());
		GetWorld()->SpawnActor(currentLevel,&planeTr);
		bIsSpawned = true;
	}
		
}



