// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding/AStarAlgo.h"
#include "Pathfinding/AStarNode.h"
#include "Chaos/Pair.h"
#include "Pathfinding/Graph.h"


AStarAlgo::~AStarAlgo()
{
}

AStarAlgo::AStarAlgo(TArray<struct Transition> XTransitions, AAStarNode* XStart, AAStarNode* XEnd)
{
	Transitions = XTransitions;
	Start = XStart;
	End = XEnd; 
}


TArray<class AAStarNode*> AStarAlgo::AStar()
{
	TArray<AAStarNode*> Open, Close , Result;
	int32 IndexClose, IndexOpen;

	if (Start == End) { return TArray<class AAStarNode*>(); } // être sur que les Nodes sont valide pas sur de devoir check ici, plus quand on clique pour choisir 

	//Staring Node 
	Start->Setg(0.f);
	Start->Seth(End);
	Start->Calcf();

	Open.Add(Start); 

	// EMPTY 
	TArray<class AAStarNode*> EmptyRoad = TArray<class AAStarNode*>();

	while (!Open.IsEmpty()) {

		AAStarNode* Q = FindSmallestF(Open);
		Open.RemoveSingle(Q); // .
		TArray<Chaos::Pair<AAStarNode*,float>> QSuccessors = FindQSuccessors(Q);

		//OUI 

		for (Chaos::Pair<AAStarNode*, float> Succ : QSuccessors) {
			if (Succ.First == End) {
				End->Parent= Q;

				Result = NodeRoad(End);
				return Result;
			} 
			else {
				float TempG = Q->GetG() + Succ.Second,
					TempH = FVector::Dist(Succ.First->GetActorLocation(), End->GetActorLocation()),
					TempF = TempG+TempH;
				IndexOpen = Open.Find(Succ.First); 
				IndexClose = Close.Find(Succ.First);
				if (  (IndexOpen != INDEX_NONE && TempF > Open[IndexOpen]->GetF() ) ||  (IndexClose != INDEX_NONE && TempF > Close[IndexClose]->GetF())) {

					continue;
				}
				else {

					Succ.First->Setg(Q->GetG() + Succ.Second);
					Succ.First->Seth(End);
					Succ.First->Calcf();
					Succ.First->Parent = Q;
					Open.Add(Succ.First);
				}
			}
		}
		Close.Push(Q);
	} 

	return EmptyRoad; // Pas de chemin 
}

AAStarNode* AStarAlgo::FindSmallestF(TArray<AAStarNode*> Array)
{
	//Jamais Empty on check avant de call la fonction
	AAStarNode* Q = Array[0];
	for (AAStarNode* Node : Array) {
		if (Node->GetF() < Q->GetF()) Q = Node;
	}
	return Q; 
}


//					<Node Sccu, Cout>
TArray<struct Chaos::Pair<AAStarNode*, float>> AStarAlgo::FindQSuccessors(AAStarNode* Q)
{
	TArray<Chaos::Pair<AAStarNode*, float >> SuccArray;
	for (Transition T : Transitions) {
		if (T.N1 == Q) { SuccArray.AddUnique(Chaos::Pair<AAStarNode*, float >(T.N2,T.Cost)); }
		if (T.N2 == Q) { SuccArray.AddUnique(Chaos::Pair<AAStarNode*, float >(T.N2, T.Cost)); } // Obligé de faire les deux car N1<->N2
	}
	return SuccArray;
}

TArray<AAStarNode*> AStarAlgo::NodeRoad(AAStarNode* Node)
{
	TArray<AAStarNode*> Chemin= TArray<AAStarNode*>();
	AAStarNode* Curr = Node;
	Chemin.Push(Curr);

	while (Curr->Parent != nullptr) {
		Chemin.Push(Curr->Parent);
		if (Curr->Parent != Curr) {
			Curr = Curr->Parent;
		}
		else return Chemin;
	}
	return Chemin;
}