// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringMovement.h"


SteeringMovement::SteeringMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Velo)
{
	AiPos = AiPawn->GetActorLocation();
	Velocity = Velo;
	this->TargetPos = TargetPos;
	this->TargetPos = TargetPos;
	this->MaxSpeed = MaxSpeed;
}

SteeringMovement::~SteeringMovement()
{
}

FVector SteeringMovement::SteeringForce()
{
	return FVector(0.f,0.f,0.f);
}
