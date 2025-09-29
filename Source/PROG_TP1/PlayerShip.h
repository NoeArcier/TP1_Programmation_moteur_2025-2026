// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerShip.generated.h"

UCLASS()
class PROG_TP1_API APlayerShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerShip();

	UPROPERTY(EditAnywhere, Category = "Laser")
	TSubclassOf<AActor> LaserToFire;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HitPoints = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxHitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score = 0;
	
	FVector TargetDirection;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Move();
	void Fire();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ReceiveDamage(float DamageAmount);
	void AddScore();

};
