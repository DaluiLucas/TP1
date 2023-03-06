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

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(BlueprintReadWrite, Category = "Components")
	UCapsuleComponent* Capsule; 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
