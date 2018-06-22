// Fill out your copyright notice in the Description page of Project Settings.

#include "TankStatics.h"

float UTankStatics::FindDeltaAngleDegress(float Angle1, float Angle2)
{
	float Delta = Angle1 - Angle2;

	if (Delta > 180.0f)
	{
		Delta = Delta - 360.0f;
	}
	else if (Delta < -180.0f)
	{
		Delta = Delta + 360.0f;
	}
	return Delta;
}

bool UTankStatics::FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle)
{
	FVector2D Normal = (Target - Start).GetSafeNormal();
	if (!Normal.IsNearlyZero())
	{
		Angle = FMath::RadiansToDegrees(FMath::Atan2(Normal.Y, Normal.X));
		return true;
	}
	return true;
}


