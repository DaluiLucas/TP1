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
	virtual FVector  Movement();

protected:
	FVector TargetPosition;
	FVector AiPosition;
	float MaxSpeed;
	FVector Velocity;
};

