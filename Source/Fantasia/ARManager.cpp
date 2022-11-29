// Fill out your copyright notice in the Description page of Project Settings.


#include "ARManager.h"


#include "EngineUtils.h"
#include "Components/InputComponent.h"
#include "GameFramework/PawnMovementComponent.h"


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

		Results = UARBlueprintLibrary::GetAllGeometries();
		 if(Results.Num() > 0)
		 {
			 ARCorePlane = Results[0];
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
	PlayerInputComponent->BindAxis("Horizontal", this, &AARManager::RightMovement);
	PlayerInputComponent->BindAxis("Vertical", this, &AARManager::ForwardMovement);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, 
		this, &AARManager::JumpAction);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, 
		this, &AARManager::JumpAction);

}

void AARManager::InputTouch(ETouchIndex::Type fingerIndex, FVector location)
{
	if(ARCorePlane != nullptr && !bIsSpawned)
	{

		GetWorld()->SpawnActor(currentLevel,&planeTr);
		bIsSpawned = true;
		sHero = static_cast<AARHero*>(UGameplayStatics::GetActorOfClass(this, hero));
	}
		
}


//Manage Hero movements
void AARManager::ForwardMovement(float inputValue)
{
	if(sHero != nullptr)
		sHero->ForwardMovement(inputValue, GetTransform().GetUnitAxis(EAxis::Type::X));
}

void AARManager::RightMovement(float inputValue)
{
	if (sHero != nullptr)
		sHero->RightMovement(inputValue, GetTransform().GetUnitAxis(EAxis::Type::Y));
}

void AARManager::JumpAction()
{
	if (sHero != nullptr)
		sHero->JumpAction();
}

void AARManager::StopJumpAction()
{
	if (sHero != nullptr)
		sHero->StopJumpAction();
}



