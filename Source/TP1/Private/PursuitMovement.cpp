// Fill out your copyright notice in the Description page of Project Settings.


#include "PursuitMovement.h"

PursuitMovement::PursuitMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Vel) : SeekMovement(AiPawn, TargetPos, MaxSpeed, Vel)
{
}

PursuitMovement::~PursuitMovement()
{
}

FVector PursuitMovement::Pursuit()
{
	float T = FVector::Dist(AiPosition, TargetPosition) * C;
	TargetPosition = TargetPosition - T;
	return Seek();
}

FVector PursuitMovement::Movement()
{
	return Pursuit();
}
