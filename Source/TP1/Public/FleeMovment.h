// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MovementBase.h>
class TP1_API FleeMovment : public MovementBase
{
public:
	FleeMovment(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Vel);
	~FleeMovment();
	FVector Flee();
	virtual FVector Movement() override;
};
