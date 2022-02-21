// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <FleeMovment.h>

class TP1_API EvasionMovement : FleeMovment
{
public:
	EvasionMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Vel);
	~EvasionMovement();
	FVector Evasion();
	virtual FVector Movement() override;
protected:
	UPROPERTY(Editinstanceonly, BlueprintReadOnly, Category = Limiter, meta = (AllowPrivateAccess = "true"))	
	float C = 0.2;
};
