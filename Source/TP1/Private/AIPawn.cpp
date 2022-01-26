// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "SeekMovement.h"
#include "FleeMovment.h"

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


	SeekMovement SeekM = SeekMovement(Cast<APawn>(this), FVector(5.f, 5.f, 1.f), MaxSpeed, Velocity);
	FleeMovment FleeM = FleeMovment(Cast<APawn>(this), FVector(5.f, 5.f, 1.f), MaxSpeed, Velocity);

	//FVector SteeringForce = Truncate(SeekM.Seek(), MaxForce);
	FVector SteeringForce = Truncate(FleeM.Flee(), MaxForce);
	FVector Acceleration = SteeringForce / Mass;
	Velocity = Truncate( Velocity + Acceleration, MaxSpeed);
	FVector Position = GetActorLocation()+Velocity;

	SetActorLocation(Position);

	//
	FVector NewForward = Velocity.GetUnsafeNormal();
	FVector ApproximateUp = GetActorUpVector().GetUnsafeNormal();
	FVector NewSide = FVector::CrossProduct(NewForward, ApproximateUp);
	FVector NewUp = FVector::CrossProduct(NewForward, NewSide);

	//SetActorRotation(FRotator(NewForward.X, NewSide.Y, 0.0f));
}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector AAIPawn::Truncate(FVector Vec, float Max)
{
	if (Vec.Size() > Max) {
		return Vec.GetUnsafeNormal()*Max;
	}
	else return Vec;
}


