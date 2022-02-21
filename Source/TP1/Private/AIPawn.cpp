// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "SeekMovement.h"
#include "FleeMovment.h"
#include "MovementBase.h"
#include "PursuitMovement.h"
#include "EvasionMovement.h"

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

	uint8 MovementTypeAsInt = (uint8)MovementType;

	//Ugly

	FVector SteeringForce;

	if (Target != nullptr) {

		if (MovementTypeAsInt == 0) SteeringForce = Truncate(SeekMovement(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);
		if (MovementTypeAsInt == 1) SteeringForce = Truncate(FleeMovment(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);
		if (MovementTypeAsInt == 2) SteeringForce = Truncate(PursuitMovement(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);

		else SteeringForce = Truncate(EvasionMovement(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);

	}

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


