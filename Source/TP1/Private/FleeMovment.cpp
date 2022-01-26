// Fill out your copyright notice in the Description page of Project Settings.


#include "FleeMovment.h"



FleeMovment::FleeMovment(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Vel)
{
	AiPos = AiPawn->GetActorLocation();
	Velocity = Vel;
	this->TargetPos = TargetPos;
	this->MaxSpeed = MaxSpeed;
}

FleeMovment::~FleeMovment()
{
}

FVector FleeMovment::Flee()
{
	FVector DesiredVelocity = ((TargetPos - AiPos)*-1).GetUnsafeNormal() * MaxSpeed;
	return DesiredVelocity - Velocity;
}
