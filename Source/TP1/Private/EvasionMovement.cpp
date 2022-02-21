// Fill out your copyright notice in the Description page of Project Settings.


#include "EvasionMovement.h"

EvasionMovement::EvasionMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Vel) : FleeMovment(AiPawn, TargetPos, MaxSpeed, Vel)
{
}

EvasionMovement::~EvasionMovement()
{
}

FVector EvasionMovement::Evasion()
{
	float T = FVector::Dist(AiPosition, TargetPosition) * C;
	TargetPosition = TargetPosition - T;
	return Flee();
}

FVector EvasionMovement::Movement()
{
	return Evasion();
}
