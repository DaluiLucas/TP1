// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "AStarNode.generated.h"

UCLASS()
class TP1_API AAStarNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStarNode();

	// Boolean indicating if the charcter can stand where the node is located  
	UPROPERTY(BlueprintReadWrite, Category = "Infos")
	bool OnOff = true; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(BlueprintReadWrite, Category = "Components")
	UCapsuleComponent* Capsule; 

	float g, h, f;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	inline void Setg(float Newg) { g = Newg; };

	inline void Seth(AAStarNode* End) { h = FVector::Distance(GetActorLocation(), End->GetActorLocation()); }; // Euclidean Distance 

	inline void Calcf() { f = g + h; };

	inline float GetF() { return f; };
	inline float GetG() { return g; };
	inline float GetH() { return h; };

	AAStarNode* Parent = nullptr;

};
