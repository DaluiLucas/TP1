// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TP1_API SeekMovement
{
public:
	SeekMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Vel);
	FVector Seek();
	~SeekMovement();

private:
	FVector TargetPos;
	FVector AiPos;
	float MaxSpeed;
	FVector Velocity;

};
