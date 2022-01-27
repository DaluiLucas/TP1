// Fill out your copyright notice in the Description page of Project Settings.


#include "FleeMovement.h"

FleeMovement::FleeMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Velo)
{
	AiPos = AiPawn->GetActorLocation();
	Velocity = Velo;
	this->TargetPos = TargetPos;
	this->TargetPos = TargetPos;
	this->MaxSpeed = MaxSpeed;
}

FleeMovement::~FleeMovement()
{
}

FVector FleeMovement::Flee()
{
	FVector DesiredVelocity = -1*((TargetPos - AiPos).GetUnsafeNormal()) * MaxSpeed;
	return DesiredVelocity - Velocity;
}


