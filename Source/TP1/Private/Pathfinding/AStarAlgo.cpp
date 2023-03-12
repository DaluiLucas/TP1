// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding/AStarAlgo.h"
#include "Pathfinding/AStarNode.h"
#include "Chaos/Pair.h"
#include "Pathfinding/Graph.h"


AStarAlgo::~AStarAlgo()
{
}

TArray<class AAStarNode*> AStarAlgo::AStar()
{
	TArray<AAStarNode*> Open, Close;

	if (Start != End && (!Start->OnOff || !End->OnOff)) { return TArray<class AAStarNode*>(); } // être sur que les Nodes sont valide pas sur de devoir check ici, plus quand on clique pour choisir 

	//Staring Node 
	Start->Setg(0.f);
	Start->Seth(End);
	Start->Calcf();

	while (!Open.IsEmpty()) {

		AAStarNode* Q = FindSmallestF(Open);
		Open.RemoveSingle(Q); // .
		TArray<Chaos::Pair<AAStarNode*,float>> QSuccessors = FindQSuccessors(Q);

		for (Chaos::Pair<AAStarNode*, float> Succ : QSuccessors) {
			if (Succ.First == End) return Close; // Retorner le chemin c'est probablement pas close
			else {
				Succ.First->Setg(Q->GetG() + Succ.Second );
				Succ.First->Seth(End);
				Succ.First->Calcf();
			}
		}

	}

	return TArray<class AAStarNode*>();
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

//TArray<class AAStarNode*> AStarAlgo::FindQSuccessors(AAStarNode* Q)
//{
//	TArray<class AAStarNode*> SuccArray;
//	for (Transition T : Transitions) {
//		if (T.N1 == Q) { SuccArray.AddUnique(T.N2); }
//		if (T.N2 == Q) { SuccArray.AddUnique(T.N1); } // Obligé de faire les deux car N1<->N2
//	}
//	return SuccArray;
//}


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