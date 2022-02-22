// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

UENUM()
enum class EMovementType : uint8 {
	SEEK = 0 UMETA(DisplayName = "Seek"),
	FLEE = 1 UMETA(DisplayName = "Flee"),
	PURSUIT = 2 UMETA(DisplayName = "Pursuit"),
	EVADE = 3 UMETA(DisplayName = "Evade"),
	ARRIVAL = 4 UMETA(DisplayName = "Arrival"),
	CIRCUIT = 5  UMETA(DisplayName = "Circuit"),
	ONEWAY = 6  UMETA(DisplayName = "OneWay"),
	TWOWAYS = 7 UMETA(DisplayName = "TwoWays")

};

UCLASS()
class TP1_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// AI mass
	UPROPERTY(Editinstanceonly, BlueprintReadOnly, Category = Limiter, meta = (AllowPrivateAccess = "true"))
	float Mass = 10.f;

	//Max Ai speed
	UPROPERTY(editinstanceonly, BlueprintReadOnly, Category = Limiter, meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 20.0f;

	//Max Ai Force
	UPROPERTY(editinstanceonly, BlueprintReadOnly, Category = Limiter, meta = (AllowPrivateAccess = "true"))
	float MaxForce = 5.0f;

	//Velocity (we are not using Unreal Velocity)
	FVector Velocity;

	//Current Target
	UPROPERTY(EditInstanceOnly, Category = "Target")
	AActor* Target;

	//Array of target
	UPROPERTY(EditInstanceOnly, Category = "Target")
	TArray<AActor*> PathArray;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector Truncate(FVector Vec, float Max);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MovementTypes, meta = (AllowPrivateAccess = "true"))
	EMovementType MovementType;

private:
	UPROPERTY(VisibleAnywhere, Category = ArcanoidePawn, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, Category = ArcanoidePawn, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = ArcanoidePawn, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComp;

	//Distance from wich we switch Target
	float MaxTargetOffset = 150.0f;

	//Used in Two ways 
	int Dir = -1;
};

