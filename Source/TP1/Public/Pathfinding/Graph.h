// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AStarNode.h"
/**
 * 
 */

struct Transition {
	class AStarNode* N1;
	class AStarNode* N2;
	int Cost;
	bool operator==(const Transition T2) { return N1 == T2.N1 && N2 == T2.N2 && Cost == T2.Cost; }
};
class TP1_API Graph
{
public:
	Graph();
	~Graph();
protected: 
	TArray<class AStarNode *> LesNodes;

	TArray<Transition> LeGraph;
public :
	//Ajoute une node dans le tablea
	//True si ajoutée
	//False si existe deja dans le graph ou pas dans les bounds de la map
	int AddNode(AStarNode* NewNode);

	bool AddTransition(Transition NTrans);

};
