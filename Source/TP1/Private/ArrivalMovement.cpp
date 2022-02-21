// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrivalMovement.h"

ArrivalMovement::ArrivalMovement(APawn* AiPawn, FVector TargetPosition, float MaxSpeed, FVector Velocity) : MovementBase(AiPawn, TargetPosition, MaxSpeed, Velocity)
{
}

ArrivalMovement::~ArrivalMovement()
{
}

FVector ArrivalMovement::Arrival()
{
	FVector TargetOffset = TargetPosition - AiPosition;
	float DistanceFromTarget = (TargetOffset).Size();
	float RampedSpeed = MaxSpeed * (DistanceFromTarget / SlowingDistance);
	float ClippedSpeed = FMath::Min(MaxSpeed, RampedSpeed);
	FVector DesiredVelocity = (ClippedSpeed / DistanceFromTarget) * TargetOffset;
	return (DesiredVelocity - Velocity);
}

FVector ArrivalMovement::Movement()
{
	return Arrival();
}
