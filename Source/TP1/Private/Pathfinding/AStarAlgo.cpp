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
	//1.  Initialize the open list and Initialize the closed list
	TArray<AAStarNode*> Open, Close , Result;

	int32 IndexClose, IndexOpen;

	if (Start == End) { return Result; } // être sur que les Nodes sont valide pas sur de devoir check ici, plus quand on clique pour choisir 

	//2 Put the starting node on the open list
	Start->Setg(0.f);
	Start->Seth(End);
	Start->Calcf();
	Open.Add(Start); 

	//3.  while the open list is not empty
	while (!Open.IsEmpty()) {

		// a) find the node with the least f on the open list, call it "Q"
		AAStarNode* Q = FindSmallestF(Open);

		//b) pop q off the open list
		Open.RemoveSingle(Q); // .

		// c) generate q's successors and set their parents to q
		TArray<Chaos::Pair<AAStarNode*,float>> QSuccessors = FindQSuccessors(Q);

		//d) for each successo
		for (Chaos::Pair<AAStarNode*, float> Succ : QSuccessors) {

			//i) if successor is the goal, stop search
			if (Succ.First == End) {
				End->Parent= Q;

				Result = NodeRoad(End);
				return Result;
			} 

			//ii) else, compute g, h and f
			else {
				float TempG = Q->GetG() + Succ.Second,
					TempH = FVector::Dist(Succ.First->GetActorLocation(), End->GetActorLocation()),
					TempF = TempG+TempH;
				IndexOpen = Open.Find(Succ.First); 
				IndexClose = Close.Find(Succ.First);

				//iii) if a node with the same position as successor is in the OPEN list which has a lower f than successor, skip this successor
				//iV) if a node with the same position as  successor  is in the CLOSED list which has a lower f than successor, skip this successor
				if (  (IndexOpen != INDEX_NONE && TempF >= Open[IndexOpen]->GetF() ) ||  (IndexClose != INDEX_NONE && TempF >= Close[IndexClose]->GetF())) {

					continue;
				}

				//Si present dans Open avec plus petit, a remplacer  
				if (IndexOpen != INDEX_NONE && TempF < Open[IndexOpen]->GetF()) {
					Open[IndexOpen]->Setg(Q->GetG() + Succ.Second);
					Open[IndexOpen]->Seth(End);
					Open[IndexOpen]->Calcf();
					Open[IndexOpen]->Parent = Q;
				}

				//V)otherwise ,add  the node to the open list
				else {
					Succ.First->Setg(Q->GetG() + Succ.Second);
					Succ.First->Seth(End);
					Succ.First->Calcf();
					Succ.First->Parent = Q;
					Open.Add(Succ.First);
				}
			}
		}
		//e) push q on the closed list
		Close.Push(Q);
	} 

	return Result;
}

AAStarNode* AStarAlgo::FindSmallestF(TArray<AAStarNode*> Array)
{
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
		if (T.N2 == Q) { SuccArray.AddUnique(Chaos::Pair<AAStarNode*, float >(T.N1, T.Cost)); } // Obligé de faire les deux car N1<->N2
	}
	return SuccArray;
}

TArray<AAStarNode*> AStarAlgo::NodeRoad(AAStarNode* Node)
{
	TArray<AAStarNode*> Chemin= TArray<AAStarNode*>();
	AAStarNode* Curr = Node;

	while (Curr->Parent != nullptr) {
		Chemin.Add(Curr);
		if (Curr->Parent != Curr) {
			Curr = Curr->Parent;
		}
		else return Chemin;
	}
	//Chemin.Add(Curr);
	return Chemin;
}