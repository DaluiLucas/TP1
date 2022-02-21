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
	ARRIVAL = 4 UMETA(DisplayName = "Arrival")
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
	
	// class Vehicule
	UPROPERTY(Editinstanceonly, BlueprintReadOnly, Category = Limiter, meta = (AllowPrivateAccess = "true"))
	float Mass = 10.f;

	UPROPERTY(editinstanceonly, BlueprintReadOnly, Category = Limiter, meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 50.0f;

	UPROPERTY(editinstanceonly, BlueprintReadOnly, Category = Limiter, meta = (AllowPrivateAccess = "true"))
	float MaxForce = 12.f;

	FVector Velocity;

	UPROPERTY(EditInstanceOnly, Category = "Target")
	AActor* Target;



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
};

