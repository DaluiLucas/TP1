// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SeekMovement.h"

#include "CoreMinimal.h"

/**
 * 
 */
class TP1_API PursuitMovement : public SeekMovement
{
public:
	PursuitMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Velo);
	~PursuitMovement();
	FVector Pursuit();
	virtual FVector SteeringForce() override;

protected:
	UPROPERTY(Editinstanceonly, BlueprintReadOnly, Category = Limiter, meta = (AllowPrivateAccess = "true"))
	float C = 0.2;
};
