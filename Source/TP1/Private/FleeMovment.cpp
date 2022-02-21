// Fill out your copyright notice in the Description page of Project Settings.


#include "FleeMovment.h"



FleeMovment::FleeMovment(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Vel) : MovementBase{ AiPawn, TargetPos, MaxSpeed, Vel }
{

}

FleeMovment::~FleeMovment()
{
}

FVector FleeMovment::Flee()
{
	FVector DesiredVelocity = ((TargetPosition - AiPosition)*-1).GetUnsafeNormal() * MaxSpeed;
	return DesiredVelocity - Velocity;
}

FVector FleeMovment::Movement()
{
	return Flee();
}
