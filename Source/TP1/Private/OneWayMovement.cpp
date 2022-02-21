// Fill out your copyright notice in the Description page of Project Settings.


#include "OneWayMovement.h"



OneWayMovement::OneWayMovement(APawn* AiPawn, AActor* Target, float MaxSpeed, FVector Velocity, TArray<AActor*> TabTarget) : ArrivalMovement(AiPawn, (Target->GetActorLocation()), MaxSpeed, Velocity)
{
	if ((TargetPosition - AiPosition).Size() < MaxTargetOffset) {
		int WhereinArray = TabTarget.Find(Target);
		if (WhereinArray != TabTarget.Num() - 1) TargetPosition = TabTarget[WhereinArray + 1]->GetActorLocation();;
	}
}

OneWayMovement::~OneWayMovement()
{
}

FVector OneWayMovement::OneWay()
{
    return Arrival();
}


FVector OneWayMovement::Movement()
{
    return OneWay();
}