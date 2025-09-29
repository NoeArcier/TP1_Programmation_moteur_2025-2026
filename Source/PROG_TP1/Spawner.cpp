// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	PointA = GetActorLocation();
	Segments = {{PointA, PointB}, {PointA, PointC}, {PointD, PointC}, {PointD, PointB}};
	SpawnDelay = FMath::FRandRange(20.f, 100.f);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Timer > SpawnDelay)
	{
		Timer = 0;
		SpawnDelay = FMath::FRandRange(20.f, 100.f);
		
		if (ObjectToSpawn)
		{
			RandomIndex = FMath::RandRange(0, 1);
			StartSegment = Segments[RandomIndex];

			EndSegment = Segments[RandomIndex + 2];
			
			if (FMath::RandRange(0, 1) == 1)
			{
				Save = StartSegment;
				StartSegment = EndSegment;
				EndSegment = Save;
			}
			
			StartPoint = GenerateRandomPoint(StartSegment[0], StartSegment[1]);
			EndPoint = GenerateRandomPoint(EndSegment[0], EndSegment[1]);

			Rotator = (EndPoint - StartPoint).Rotation();
			
			GetWorld()->SpawnActor<AActor>(ObjectToSpawn, StartPoint, Rotator);
		}
	} else
	{
		Timer += 100 * DeltaTime;
	}
}

FVector ASpawner::GenerateRandomPoint(FVector A, FVector B) const
{	
	if (A.Equals(B))
	{
		return A; // Segment nul
	}

	float random = FMath::FRand(); // [0,1)
	return FMath::Lerp(A, B, random);
}

