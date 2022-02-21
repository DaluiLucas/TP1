// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MovementBase.h>
class TP1_API SeekMovement : public MovementBase
{
public:
	SeekMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Vel);
	FVector Seek();
	~SeekMovement();
	virtual FVector Movement() override;
};
