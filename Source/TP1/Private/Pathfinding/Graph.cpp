// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding/Graph.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Pathfinding/AStarNode.h"


Graph::Graph()
{
}

Graph::Graph(TArray<class AAStarNode*> Nodes, const UObject* World)
{
	LesNodes = Nodes; 
	TheWorld = World;
}

Graph::~Graph()
{
}

TArray<Transition> Graph::MakeGraph()
{
	int Numb=0;
	for (AAStarNode* Node : LesNodes) {
		Numb++;
		if (!Node->OnOff) continue; 
		for (int i = Numb; i < LesNodes.Num(); ++i) {
			if (!LesNodes[i]->OnOff) continue;
			FVector Start = Node->GetActorLocation(); 
			FVector End = LesNodes[i]->GetActorLocation();
			TArray<AActor*> Ignore; 
			FHitResult HitRes; 
			bool Hit = UKismetSystemLibrary::LineTraceSingle(TheWorld, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, Ignore, EDrawDebugTrace::None, HitRes, true);
			//if(!Hit) UKismetSystemLibrary::LineTraceSingle(TheWorld, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, Ignore, EDrawDebugTrace::ForDuration, HitRes, true); debug
			if (!Hit) {
				Transition Temp;
				Temp.N1 = Node;
				Temp.N2 = LesNodes[i];
				Temp.Cost = (float)FVector::Distance(Start , End);

				LeGraph.Add(Temp);
			}
		}
	} 
	return LeGraph;
}

