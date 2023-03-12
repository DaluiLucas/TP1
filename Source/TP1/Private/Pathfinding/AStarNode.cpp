// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding/AStarNode.h"

// Sets default values
AAStarNode::AAStarNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Visual representation in game 
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(false);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	Capsule->SetCapsuleRadius(42);
	Capsule->SetCapsuleHalfHeight(98);
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = Capsule;
	MeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAStarNode::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AAStarNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

