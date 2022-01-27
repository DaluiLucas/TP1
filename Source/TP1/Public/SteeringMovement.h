// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TP1_API SteeringMovement
{
public:
	SteeringMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Velo);
	~SteeringMovement();

	virtual FVector SteeringForce();

protected:
	FVector TargetPos;
	FVector AiPos;
	float MaxSpeed;
	FVector Velocity;

};
