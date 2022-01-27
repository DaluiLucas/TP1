// Fill out your copyright notice in the Description page of Project Settings.


#include "SeekMovement.h"

#include "AIPawn.h"

SeekMovement::SeekMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed , FVector Velo) : SteeringMovement(AiPawn, TargetPos, MaxSpeed, Velo)
{
}

SeekMovement::~SeekMovement()
{

}



FVector SeekMovement::Seek()
{
	FVector DesiredVelocity = (TargetPos - AiPos).GetUnsafeNormal() * MaxSpeed;
	return DesiredVelocity - Velocity;
}

FVector SeekMovement::SteeringForce()
{
	return Seek();
}
//normalize(v) = to_unit(v) = v/|v|