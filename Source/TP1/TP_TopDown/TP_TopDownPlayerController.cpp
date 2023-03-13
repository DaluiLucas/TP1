// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "Pathfinding/NodeBuilder.h"
#include "Pathfinding/AStarNode.h"
#include "BehaviorTree/BehaviorTree.h"

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
	if (PathArray.Num() > 0) {

		//PAS BIEN DU TOUT 
		TArray<AAStarNode*> NodeArray = MyNodeBuilder->getNodeArray();
		AAStarNode* ClosestToChar = NodeArray[0], *ClosestToTarget = NodeArray[0];
		float DistChar = FVector::Distance(GetPawn()->GetTargetLocation(), NodeArray[0]->GetTargetLocation());
		float DistTarget= FVector::Distance(GetPawn()->GetTargetLocation(), NodeArray[0]->GetTargetLocation());
		for (AAStarNode* Node : NodeArray) {
			if (FVector::Distance(GetPawn()->GetTargetLocation(), Node->GetTargetLocation()) < DistChar) { 
				ClosestToChar = Node;
				DistChar = FVector::Distance(GetPawn()->GetTargetLocation(), Node->GetTargetLocation());
			}
			if (FVector::Distance(PathArray[0]->GetActorLocation(), Node->GetTargetLocation()) < DistTarget) {
				ClosestToTarget = Node;
				DistTarget = FVector::Distance(PathArray[0]->GetActorLocation(), Node->GetTargetLocation());
			}
		}


		TheWay = MyNodeBuilder->RunAStar(ClosestToChar, ClosestToTarget);
		
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);


	}
}

void ATP_TopDownPlayerController::LoopPathFunction() {
	GEngine->AddOnScreenDebugMessage(25, 2.f, FColor::Red, TEXT("Loop"));

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
	
	//// Move towards mouse pointer or touch
	//APawn* ControlledPawn = GetPawn();
	//if (ControlledPawn != nullptr)
	//{
	//	FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
	//	ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	//}

	//Delete ?

}

void ATP_TopDownPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		//// We move there and spawn some particles
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);

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
