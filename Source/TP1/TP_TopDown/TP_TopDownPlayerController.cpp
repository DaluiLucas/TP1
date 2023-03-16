// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "Pathfinding/NodeBuilder.h"
#include "Pathfinding/AStarNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Algo/Reverse.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TP_TopDownCharacter.h"
#include "Engine/World.h"
#include "Engine/TargetPoint.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ATP_TopDownPlayerController::ATP_TopDownPlayerController()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ATP_TopDownPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	//Trouver le Builder pas empty
	MyNodeBuilder = Cast<ANodeBuilder>(UGameplayStatics::GetActorOfClass(GetWorld(), ANodeBuilder::StaticClass()));

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATP_TopDownPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CanMove && TheWay.Num() > 1 && FVector::Distance(GetPawn()->GetTargetLocation(), TheWay[0]->GetActorLocation()) < Thresh) {
		if (Loop) {
			AAStarNode* N = TheWay[0];
			TheWay.Add(N);
		}
		TheWay.RemoveAt(0);
		if(TheWay.Num()>0) UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, TheWay[0]->GetActorLocation());
		else {
			if (!Loop)CanMove = false;
		}
	}

}

void ATP_TopDownPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATP_TopDownPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATP_TopDownPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATP_TopDownPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ATP_TopDownPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ATP_TopDownPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ATP_TopDownPlayerController::OnTouchReleased);

		// Setup Movement Key
		EnhancedInputComponent->BindAction(DeleteTarget, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::DeleteTargetFromArray);
		EnhancedInputComponent->BindAction(FollowPAth, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::FollowPathFunction);
		EnhancedInputComponent->BindAction(LoopPath, ETriggerEvent::Triggered, this, &ATP_TopDownPlayerController::LoopPathFunction);

	}
}

void ATP_TopDownPlayerController::DeleteTargetFromArray() {
	if (PathArray.Num() > 0) {
		AActor* Popped = PathArray.Pop(); 
		Popped->Destroy();
		GEngine->AddOnScreenDebugMessage(25, 2.f, FColor::Red, TEXT("Deleted"));
	}
}

void ATP_TopDownPlayerController::FollowPathFunction() {
	GEngine->AddOnScreenDebugMessage(25, 2.f, FColor::Red, TEXT("Follow"));
	Loop = false;
	PathCreator();

}

void ATP_TopDownPlayerController::LoopPathFunction() {
	GEngine->AddOnScreenDebugMessage(25, 2.f, FColor::Red, TEXT("Loop"));
	Loop = true;
	PathCreator();

}

void ATP_TopDownPlayerController::PathCreator() {
	if (MyNodeBuilder == nullptr) return;

	if (PathArray.Num() > 0) {
		TArray<AAStarNode*> NodeArray = MyNodeBuilder->getNodeArray();
		AAStarNode* ClosestToStart, * ClosestToEnd = NodeArray[0];

		for (int i = 0; i < PathArray.Num(); ++i)
		{

			float DistStart = FVector::Distance(GetPawn()->GetTargetLocation(), NodeArray[i]->GetTargetLocation());
			float DistEnd = FVector::Distance(GetPawn()->GetTargetLocation(), NodeArray[i]->GetTargetLocation());

			if (i != 0) { ClosestToStart = ClosestToEnd; }
			else ClosestToStart = NodeArray[i];

			ClosestToEnd = NodeArray[i];

			for (AAStarNode* Node : NodeArray) {
				if (i == 0 && FVector::Distance(GetPawn()->GetTargetLocation(), Node->GetTargetLocation()) < DistStart && Node->OnOff) {
					ClosestToStart = Node;
					DistStart = FVector::Distance(GetPawn()->GetTargetLocation(), Node->GetTargetLocation());
				}
				if (FVector::Distance(PathArray[i]->GetActorLocation(), Node->GetTargetLocation()) < DistEnd && Node->OnOff) {
					ClosestToEnd = Node;
					DistEnd = FVector::Distance(PathArray[i]->GetActorLocation(), Node->GetTargetLocation());
				}
			}

			TArray<AAStarNode*>NewNodesToAdd = MyNodeBuilder->RunAStar(ClosestToStart, ClosestToEnd);
			Algo::Reverse(NewNodesToAdd);
			TheWay.Append(NewNodesToAdd);

		}
		CanMove = true;
		if (Loop) {
			TArray<AAStarNode*>NewNodesToAdd = MyNodeBuilder->RunAStar(ClosestToEnd, TheWay[0]);
			Algo::Reverse(NewNodesToAdd);
			TheWay.Append(NewNodesToAdd);
		}
		if (TheWay.Num() > 0) UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, TheWay[0]->GetActorLocation());
	}
}
void ATP_TopDownPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATP_TopDownPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

}

void ATP_TopDownPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		UWorld* World = GetWorld();
		if (World != nullptr && TargetClass != nullptr) {
			FTransform SpawnTransform = FTransform();
			SpawnTransform.SetLocation(CachedDestination );
			AActor* SpawnedTarget = World->SpawnActor<AActor>(TargetClass, SpawnTransform);
			PathArray.Add(SpawnedTarget);
		}
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ATP_TopDownPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATP_TopDownPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
