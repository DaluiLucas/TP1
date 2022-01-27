// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TP1_API SeekMovement
{
public:
	SeekMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Velo);
	FVector Seek();
	~SeekMovement();

protected:
	FVector TargetPos;
	FVector AiPos;
	float MaxSpeed;
	FVector Velocity;

};
