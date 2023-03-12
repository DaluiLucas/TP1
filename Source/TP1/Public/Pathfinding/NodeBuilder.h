// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Pathfinding/Graph.h"

#include "NodeBuilder.generated.h"

UCLASS()
class TP1_API ANodeBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeBuilder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MakeGraph();

	float X, Y;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float DistTrace = 150.f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class AAStarNode> Node;

	TArray<AAStarNode*> NodeArray;

	class Graph NodesGraph;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Box")
	class UBoxComponent* Box; 


};
