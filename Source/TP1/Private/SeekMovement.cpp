// Fill out your copyright notice in the Description page of Project Settings.


#include "SeekMovement.h"

SeekMovement::SeekMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Vel) : MovementBase{ AiPawn, TargetPos, MaxSpeed, Vel }
{
}

SeekMovement::~SeekMovement()
{

}

FVector SeekMovement::Movement()
{
	return Seek();
}

FVector SeekMovement::Seek()
{
	FVector DesiredVelocity = (TargetPosition - AiPosition).GetUnsafeNormal() * MaxSpeed;
	return DesiredVelocity - Velocity;
}
//normalize(v) = to_unit(v) = v/|v|