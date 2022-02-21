// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArrivalMovement.h"
/**
 * 
 */
class TP1_API CircuitMovement : public ArrivalMovement
{
public:
	CircuitMovement(APawn* AiPawn, AActor* Target, float MaxSpeed, FVector Velocity, TArray<AActor*> TabTarget);
	~CircuitMovement();
	FVector Circuit();
	virtual FVector Movement() override;

private:
	float MaxTargetOffset = 150.0f;

};
