// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SteeringMovement.h"

#include "CoreMinimal.h"

/**
 * 
 */
class TP1_API FleeMovement : public SteeringMovement
{
public:
	FleeMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Velo);
	~FleeMovement();
	FVector Flee();

	virtual FVector SteeringForce() override;
};
