// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "SeekMovement.h"


#include "SeekMovement.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	SeekMovement SeekM = SeekMovement(Cast<APawn>(this), FVector(5.f, 5.f, 5.f), MaxSpeed);
	FVector SteeringForce = SeekM.Seek().GetClampedToMaxSize(MaxForce);
	FVector Acceleration = SteeringForce / Mass;
	FVector Velocity = (GetVelocity() + Acceleration).GetClampedToMaxSize(MaxSpeed);
	FVector Position = GetActorLocation()+Velocity;

	//
	Velocity.Normalize();
	FVector NewForward = Velocity;
	FVector ApproximateUp = GetActorUpVector();
	ApproximateUp.Normalize();
	FVector NewSide = FVector::CrossProduct(NewForward, ApproximateUp);
	FVector NewUp = FVector::CrossProduct(NewForward, NewSide);

	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Red, FString::Printf(TEXT("VectorForw : %f - %f - %f"), NewForward.X, NewForward.Y, NewForward.Z));
	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Green, FString::Printf(TEXT("NewSide : %f - %f - %f"), NewSide.X, NewSide.Y, NewSide.Z));
	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Blue, FString::Printf(TEXT("NewUp : %f - %f - %f"), NewUp.X, NewUp.Y, NewUp.Z));

	this->SetActorLocation(FVector(NewForward.X , NewSide.Y, NewUp.Z));
}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

