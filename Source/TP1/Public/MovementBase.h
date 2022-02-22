// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TP1_API MovementBase
{
public:
	MovementBase(APawn* AiPawn, FVector TargetPosition, float MaxSpeed, FVector Velocity);
	virtual ~MovementBase();

	//virtual function overriden by child funtion to create custom movement
	virtual FVector  Movement();

protected:
	//Target Position
	FVector TargetPosition;

	//AI Position
	FVector AiPosition;

	//Max Ai Speed
	float MaxSpeed;

	//AI Velocity
	FVector Velocity;
};

