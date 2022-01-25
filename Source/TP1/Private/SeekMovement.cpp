// Fill out your copyright notice in the Description page of Project Settings.


#include "SeekMovement.h"

#include "AIPawn.h"

SeekMovement::SeekMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed=500.0f)
{
	AiPos = AiPawn->GetActorLocation();
	Velocity = AiPawn->GetVelocity();
	TargetPos = TargetPos;
	TargetPos = TargetPos;
	MaxSpeed = MaxSpeed;
}

SeekMovement::~SeekMovement()
{

}

FVector SeekMovement::Seek()
{
	FVector DesiredVelocity = TargetPos - AiPos;
	if( !DesiredVelocity.IsNormalized()) DesiredVelocity.Normalize();
	DesiredVelocity *= MaxSpeed;
	return DesiredVelocity - Velocity;
}

//normalize(v) = to_unit(v) = v/|v|