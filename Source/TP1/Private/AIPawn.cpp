// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "SeekMovement.h"
#include "FleeMovement.h"
#include "PursuitMovement.h"
#include "SteeringMovement.h"

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

	Velocity = FVector(-10.f, -10.f, 0.f);
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
	//FleeMovement FleeM = FleeMovement(Cast<APawn>(this), FVector(5.f, 5.f, 5.f), MaxSpeed, Velocity);
	//FVector SteeringForce = Truncate(FleeM.Flee(), MaxForce);

	//SeekMovement SeekM = SeekMovement(Cast<APawn>(this), FVector(5.f,5.f,5.f), MaxSpeed, Velocity);
	//FVector SteeringForce = Truncate(SeekM.Seek(), MaxForce);

	//PursuitMovement PursuitM = PursuitMovement(Cast<APawn>(this), FVector(5.f,5.f,5.f), MaxSpeed, Velocity);
	//FVector SteeringForce = Truncate(PursuitM.Pursuit(), MaxForce);
	FVector SteeringForce;
	if (MovementType == 0) {
		SteeringForce = Truncate(FleeMovement(Cast<APawn>(this), FVector(5.f, 5.f, 5.f), MaxSpeed, Velocity).SteeringForce(), MaxForce);
	}
	if (MovementType == 1) {
		SteeringForce = Truncate(SeekMovement(Cast<APawn>(this), FVector(5.f, 5.f, 5.f), MaxSpeed, Velocity).SteeringForce(), MaxForce);
	}
	if (MovementType == 2) {
		SteeringForce = Truncate(PursuitMovement(Cast<APawn>(this), FVector(5.f, 5.f, 5.f), MaxSpeed, Velocity).SteeringForce(), MaxForce);
	}


	FVector Acceleration = SteeringForce / Mass;
	Velocity = Truncate(Velocity + Acceleration, MaxSpeed);
	FVector Position = GetActorLocation()+Velocity;

	//
	FVector NewForward = Velocity.GetUnsafeNormal();
	FVector ApproximateUp = GetActorUpVector().GetUnsafeNormal();
	FVector NewSide = FVector::CrossProduct(NewForward, ApproximateUp);
	FVector NewUp = FVector::CrossProduct(NewForward, NewSide);

	SetActorLocation(FVector(Position.X,Position.Y , 0.0f));
	SetActorRotation(FRotator(Velocity.Rotation()));
}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector AAIPawn::Truncate(FVector Vect, float MaxS)
{
	if (Vect.Size() > MaxS) {
		return Vect.GetUnsafeNormal() * MaxS;
	}
	else return Vect;
}

