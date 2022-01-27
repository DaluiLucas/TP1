// Fill out your copyright notice in the Description page of Project Settings.


#include "PursuitMovement.h"
#include "SeekMovement.h"

PursuitMovement::PursuitMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Velo) : SeekMovement(AiPawn, TargetPos, MaxSpeed, Velo)
{

}

PursuitMovement::~PursuitMovement()
{
}

FVector PursuitMovement::Pursuit() {
	float T = FVector::Dist(AiPos,TargetPos) * C;
	TargetPos = TargetPos - T;
	return Seek();
}