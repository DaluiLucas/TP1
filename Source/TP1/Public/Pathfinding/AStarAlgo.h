// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

struct MyNode {
	class AAStarNode* N1;
	float f, g, h;
	class AAStarNode* Parent;
};

class TP1_API AStarAlgo
{
public:
	AStarAlgo()=delete; // ?
	AStarAlgo(TArray<struct Transition > XTransitions, class AAStarNode* XStart, class AAStarNode* XEnd);

	~AStarAlgo();

	///
	/// s € S : s = Une Transition , S = le graph complet 
	/// h(s) : Heuristique, ici Euclidiean Distance comme on peut aller dans tous les sens, h(s) c'est la distance euclidiean entre s et la Target 
	/// g(s) : le cout du movement entre s et le starting point en passant par le chemin actuel, donc pour s' g(s') = g(s)+Transition(s,s').Cout
	/// f(s) : g(s)+h(s)
	///

public:

	class AAStarNode* Start;
	class AAStarNode* End;

	TArray<struct Transition> Transitions;

	// A* Search Algorithm
	TArray<class AAStarNode*> AStar(); 

	//Find Smallest F Value from given array
	AAStarNode* FindSmallestF(TArray< class AAStarNode*> Open);

	// Find all successors of Q in Transition
	TArray<struct Chaos::Pair<AAStarNode*, float>> FindQSuccessors(AAStarNode* Q);

	//Return All Node to go from Start to End
	TArray<AAStarNode*> NodeRoad(AAStarNode* Node);


	inline int Test() { return Transitions.Num(); }
};
