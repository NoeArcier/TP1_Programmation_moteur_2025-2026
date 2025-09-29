// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class PROG_TP1_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> ObjectToSpawn;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rectangle")
	FVector PointA;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rectangle")
	FVector PointB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rectangle")
	FVector PointC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rectangle")
	FVector PointD;
	
	int SpawnDelay;
	

	int Timer = 0;

	FVector StartPoint;
	FVector EndPoint;
	
	int RandomIndex;
	TArray<TArray<FVector>> Segments;
	
	TArray<FVector> StartSegment;
	TArray<FVector> EndSegment;
	TArray<FVector> Save;

	FRotator Rotator;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector GenerateRandomPoint(FVector A, FVector B) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
