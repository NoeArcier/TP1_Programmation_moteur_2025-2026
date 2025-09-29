// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerShip::APlayerShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = StaticMesh;
}

void APlayerShip::MoveForward(float Value)
{
	TargetDirection.X = Value;
	if (Value != 0.0f)
	{
		Move();
	}
	
}

void APlayerShip::MoveRight(float Value)
{
	TargetDirection.Y = Value;
	if (Value != 0.0f)
	{
		Move();
	}
}

void APlayerShip::Move()
{
	FRotator TargetRotation = TargetDirection.Rotation();
	FRotator CurrentRotation = GetActorRotation();

	float InterpSpeed = 2.f;
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, FApp::GetDeltaTime(), InterpSpeed);
	SetActorRotation(NewRotation);
	AddMovementInput(MovementComponent->GetForwardVector(), 10);
}

void APlayerShip::Fire()
{
	GetWorld()->SpawnActor<AActor>(LaserToFire, GetActorLocation(), GetActorRotation());
}

// Called when the game starts or when spawned
void APlayerShip::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add("Ship");
	MaxHitPoints = HitPoints;
}

// Called every frame
void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

void APlayerShip::ReceiveDamage(float DamageAmount)
{
	if (HitPoints > DamageAmount)
	{
		HitPoints -= DamageAmount;
	} else
	{
		HitPoints = 0;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
		// Game Over
	}
}

void APlayerShip::AddScore()
{
	Score++;
}

// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed,this, &APlayerShip::Fire);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerShip::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerShip::MoveRight);
}

