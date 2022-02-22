// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArrivalMovement.h"
/**
 * This class is not Used
 */
class TP1_API CircuitMovement : public ArrivalMovement
{
public:
	CircuitMovement(APawn* AiPawn, AActor* Target, float MaxSpeed, FVector Velocity, TArray<AActor*> TabTarget);
	~CircuitMovement();
	FVector Circuit();
	virtual FVector Movement() override;

private:

	//Target offset before swapping target
	float MaxTargetOffset = 150.0f;

};
