// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "SeekMovement.h"
#include "FleeMovment.h"
#include "MovementBase.h"
#include "PursuitMovement.h"
#include "ArrivalMovement.h"
#include "EvasionMovement.h"
#include "CircuitMovement.h"
#include "OneWayMovement.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Root Component and Mesh
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(RootComponent);

	//Set Base Velocity could be done in .h but w/e
	Velocity = FVector(0.f, 0.f, 0.f);

}

// Called when the game starts or when spawned
//Not used
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

	//Steering Force depending on Enmu value
	if (Target != nullptr) {

		if (MovementTypeAsInt == 0) SteeringForce = Truncate(SeekMovement(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);
		if (MovementTypeAsInt == 1) SteeringForce = Truncate(FleeMovment(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);
		if (MovementTypeAsInt == 2) SteeringForce = Truncate(PursuitMovement(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);
		if (MovementTypeAsInt == 3) SteeringForce = Truncate(EvasionMovement(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);
		if (MovementTypeAsInt == 4) SteeringForce = Truncate(ArrivalMovement(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);
		if (MovementTypeAsInt == 5) {
			//WrongPlace ?
			if ((Target->GetActorLocation() - this->GetActorLocation()).Size() < MaxTargetOffset && PathArray.Num() != 0) {
				//If close to the target, get go for the next target
				int WhereinArray = PathArray.Find(Target);

				//If last target in Array goes back yo the first one
				if (WhereinArray == PathArray.Num()-1) Target = PathArray[0];
				else Target = PathArray[WhereinArray + 1];
			}
			SteeringForce = Truncate(ArrivalMovement(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);
		}
		if (MovementTypeAsInt == 6) {

			if ((Target->GetActorLocation() - this->GetActorLocation()).Size() < MaxTargetOffset && PathArray.Num() != 0) {
				int WhereinArray = PathArray.Find(Target);
				if (WhereinArray != PathArray.Num() - 1) Target = PathArray[WhereinArray + 1];
			}
			SteeringForce = Truncate(ArrivalMovement(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);
		}

		if (MovementTypeAsInt == 7) {
			if ((Target->GetActorLocation() - this->GetActorLocation()).Size() < MaxTargetOffset && PathArray.Num() != 0) {
				//fonctionne pas si plusieur fois le m^me acteur
				int WhereinArray = PathArray.Find(Target);
				if (WhereinArray == PathArray.Num() - 1 || WhereinArray == 0) Dir= Dir*-1;
				Target = PathArray[WhereinArray + Dir];
			}
			SteeringForce = Truncate(ArrivalMovement(Cast<APawn>(this), Target->GetActorLocation(), MaxSpeed, Velocity).Movement(), MaxForce);
		}
	}

	//find new Position
	FVector Acceleration = SteeringForce / Mass;
	Velocity = Truncate( Velocity + Acceleration, MaxSpeed);
	FVector Position = GetActorLocation()+Velocity;
	SetActorLocation(Position);

	// Find new Rotation
	FVector NewForward = Velocity.GetUnsafeNormal();
	FVector ApproximateUp = GetActorUpVector().GetUnsafeNormal();
	FVector NewSide = FVector::CrossProduct(NewForward, ApproximateUp);
	FVector NewUp = FVector::CrossProduct(NewForward, NewSide);
	SetActorRotation(NewForward.Rotation());
}

// Not Used
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//truncate Vector funciton
FVector AAIPawn::Truncate(FVector Vec, float Max)
{
	if (Vec.Size() > Max) {
		return Vec.GetUnsafeNormal()*Max;
	}
	else return Vec;
}


