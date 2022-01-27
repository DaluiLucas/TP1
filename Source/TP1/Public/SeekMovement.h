// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SteeringMovement.h"

#include "CoreMinimal.h"

/**
 * 
 */
class TP1_API SeekMovement : public SteeringMovement
{
public:
	SeekMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Velo);
	FVector Seek();
	~SeekMovement();
	virtual FVector SteeringForce() override;

};
