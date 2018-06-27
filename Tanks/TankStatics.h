// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TankStatics.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UTankStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//** Obliczenie ró¿nicy k¹ta 180/-180 
	UFUNCTION(BlueprintCallable, Category = "Math")
	static float FindDeltaAngleDegress(float Angle1, float Angle2);

	UFUNCTION(BlueprintPure, Category = "Math|Rotator", meta = (Keywords = "rotation rotate"))
	static bool FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle);
	
};
