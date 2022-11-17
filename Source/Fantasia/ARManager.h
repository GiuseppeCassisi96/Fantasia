// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AugmentedReality/Public/ARBlueprintLibrary.h"
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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	UARTrackedGeometry* ARCorePlane;
	UPROPERTY()
	TArray<UARTrackedGeometry*> Geometries;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
