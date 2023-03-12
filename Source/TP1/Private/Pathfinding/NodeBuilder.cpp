// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding/NodeBuilder.h"
#include "Components/BoxComponent.h"
#include "Pathfinding/AStarNode.h"
#include "Kismet/KismetSystemLibrary.h"



// Sets default values
ANodeBuilder::ANodeBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
}

// Called when the game starts or when spawned
void ANodeBuilder::BeginPlay()
{
	Super::BeginPlay();
	FVector Extent = Box->GetScaledBoxExtent();
	X = Extent.X;
	Y = Extent.Y;

	float TempX = X * -1;
	float TempY;

	while (TempX < X) {
		TempY = Y * -1;
		while (TempY < Y) {

			FVector Start = FVector(TempX+ Box->GetRelativeLocation().X, TempY+ Box->GetRelativeLocation().Y, Extent.Z+Box->GetRelativeLocation().Z);
			FVector End = FVector(TempX + Box->GetRelativeLocation().X,TempY + Box->GetRelativeLocation().Y, -50.f);
			const TArray<AActor* > Ignore;
			FHitResult Result;
			UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1, false, Ignore, EDrawDebugTrace::None, Result, true);
			TempY += DistTrace;

			UWorld* World = GetWorld();
			if (World != nullptr && Node != nullptr) {
				FTransform SpawnTransform = FTransform();
				SpawnTransform.SetLocation(Result.Location + FVector(0.f,0.f,10.f));
				AAStarNode* SpawnedNode = World->SpawnActor<AAStarNode>(Node,SpawnTransform);
				NodeArray.Add(SpawnedNode);
			}

		}
		TempX += DistTrace;
	}

	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), NodeArray.Num()));
	MakeGraph();
}

void ANodeBuilder::MakeGraph()
{
	NodesGraph = Graph(NodeArray, GetWorld());
	NodesGraph.MakeGraph();
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Blue, FString::Printf(TEXT("%d"), NodesGraph.LeGraph.Num()));

}

// Called every frame
void ANodeBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

