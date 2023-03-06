// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding/Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

int Graph::AddNode(AStarNode* NewNode)
{
	return LesNodes.AddUnique(NewNode);

}

bool Graph::AddTransition(Transition NTrans)
{
	for (Transition T : LeGraph) {
		if (T == NTrans) {
			return false;
		}
	}
	LeGraph.Add(NTrans);
	return true;
}
