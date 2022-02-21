// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <SeekMovement.h>
/**
 * 
 */
class TP1_API PursuitMovement : public SeekMovement
{
public:
	PursuitMovement(APawn* AiPawn, FVector TargetPos, float MaxSpeed, FVector Vel);
	~PursuitMovement();
	FVector Pursuit();
	virtual FVector Movement() override;

protected:
	UPROPERTY(Editinstanceonly, BlueprintReadOnly, Category = Limiter, meta = (AllowPrivateAccess = "true"))
	float C = 0.3;
};
