// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AugmentedReality/Public/ARBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ARLevel.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "ARManager.generated.h"

UCLASS()
class FANTASIA_API AARManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AARManager();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ARSessionData")
	UARSessionConfig* ARSession;
	UPROPERTY(EditDefaultsOnly,Category="CurrentLevel")
	TSubclassOf<APawn> currentLevel;
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	UCameraComponent* CameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	UARPlaneGeometry* ARCorePlane;
	bool bScanIsComplete;
	bool bIsTracked;
	bool bIsSpawned;
	FTransform planeTr;
	FVector2D ScreenSize;
	TArray<FARTraceResult> Results;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void InputTouch(ETouchIndex::Type fingerIndex, FVector location);

};
