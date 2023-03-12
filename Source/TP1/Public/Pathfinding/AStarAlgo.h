// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TP1_API AStarAlgo
{
public:
	AStarAlgo()=delete; // ?
	AStarAlgo(TArray<struct Transition > Transitions, class AAStarNode* Start, class AAStarNode* End) : Transitions(Transitions) , Start(Start), End(End) {};

	~AStarAlgo();

	///
	/// s € S : s = Une Transition , S = le graph complet 
	/// h(s) : Heuristique, ici Euclidiean Distance comme on peut aller dans tous les sens, h(s) c'est la distance euclidiean entre s et la Target 
	/// g(s) : le cout du movement entre s et le starting point en passant par le chemin actuel, donc pour s' g(s') = g(s)+Transition(s,s').Cout
	/// f(s) : g(s)+h(s)
	///
protected:
	TArray<struct Transition> Transitions;
	class AAStarNode* Start;
	class AAStarNode* End;

public:
	TArray<class AAStarNode*> AStar(); 

	AAStarNode* FindSmallestF(TArray< class AAStarNode*> Open);

	TArray<struct Chaos::Pair<AAStarNode*, float>> FindQSuccessors(AAStarNode* Q);
};
