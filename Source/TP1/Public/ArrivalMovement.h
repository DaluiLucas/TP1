// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MovementBase.h>
/**
 * 
 */
class TP1_API ArrivalMovement : public MovementBase
{
public:
	ArrivalMovement(APawn* AiPawn, FVector TargetPosition, float MaxSpeed, FVector Velocity);
	~ArrivalMovement();
	FVector Arrival();
	virtual FVector Movement() override;

private:

	//Distance from wich the AI start to slow down
	float SlowingDistance = 500;

};
