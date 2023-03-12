// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */

struct Transition {
	class AAStarNode* N1;
	class AAStarNode* N2;
	float Cost; //Cost = Distance
	//inline bool operator==( const Transition& T2) { return (N1->GetActorLocation() == T2.N1->GetActorLocation() && N2->GetActorLocation() == T2.N2->GetActorLocation() && Cost == T2.Cost); }
};

class TP1_API Graph
{
public:
	Graph();
	Graph( TArray<class AAStarNode*> Nodes, const UObject* World );
	~Graph();
protected: 
	TArray<class AAStarNode*> LesNodes;


	const UObject* TheWorld;
public :
	TArray<Transition> LeGraph;

	TArray<Transition> MakeGraph();

};
