// Fill out your copyright notice in the Description page of Project Settings.


#include "ARManager.h"

// Sets default values
AARManager::AARManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AARManager::BeginPlay()
{
	Super::BeginPlay();
	UARBlueprintLibrary::StartARSession(ARSession);
}

// Called every frame
void AARManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Geometries = UARBlueprintLibrary::GetAllGeometries();
	for (auto plane : Geometries)
	{
		UARBlueprintLibrary::DebugDrawTrackedGeometry(plane, GetWorld(), FLinearColor::Red);
	}
}

// Called to bind functionality to input
void AARManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

