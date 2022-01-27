// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TP1_API FleeMovement
{
public:
	FleeMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Velo);
	~FleeMovement();
	FVector Flee();
private:
	FVector TargetPos;
	FVector AiPos;
	float MaxSpeed;
	FVector Velocity;
};
