// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementBase.h"


MovementBase::MovementBase(APawn* AiPawn, FVector TargetPosition, float MaxSpeed, FVector Velocity): TargetPosition(TargetPosition), MaxSpeed(MaxSpeed), Velocity(Velocity)
{
	AiPosition = AiPawn->GetActorLocation();

}

MovementBase::~MovementBase()
{
}

FVector MovementBase::Movement()
{
	return FVector();
}


