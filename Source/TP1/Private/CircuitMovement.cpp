// Fill out your copyright notice in the Description page of Project Settings.


#include "CircuitMovement.h"

CircuitMovement::CircuitMovement(APawn* AiPawn, AActor* Target, float MaxSpeed, FVector Velocity, TArray<AActor*> TabTarget) : ArrivalMovement(AiPawn, (Target->GetActorLocation()) , MaxSpeed, Velocity)
{
	// If close to the target, get go for the next target
	if ((TargetPosition - AiPosition).Size() < MaxTargetOffset) {
		int WhereinArray = TabTarget.Find(Target);
		if (WhereinArray == TabTarget.Num()-1) TargetPosition = TabTarget[0]->GetActorLocation();
		else TargetPosition = TabTarget[WhereinArray + 1 ]->GetActorLocation();
	}
}

CircuitMovement::~CircuitMovement()
{
}

FVector CircuitMovement::Circuit()
{
	
	return Arrival();
}

FVector CircuitMovement::Movement()
{
	return Circuit();
}
