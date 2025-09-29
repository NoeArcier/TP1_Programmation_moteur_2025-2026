// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteor.h"

#include "PlayerShip.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMeteor::AMeteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = StaticMesh;

}

// Called when the game starts or when spawned
void AMeteor::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(15.f);
	this->OnActorBeginOverlap.AddDynamic(this, &AMeteor::OnOverlap);

	HitPoints = FMath::RandRange(1, 4);
	SetActorScale3D(GetActorScale3D() * (0.8f + 0.2f/HitPoints));
	
}

// Called every frame
void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeteor::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag("Laser"))
		{
			OtherActor->Destroy();

			if (HitPoints > 1)
			{
				HitPoints--;
				SetActorScale3D(GetActorScale3D() * (0.8f + 0.2f/HitPoints));
			} else
			{
				AActor* Ship = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerShip::StaticClass());
				Cast<APlayerShip>(Ship)->AddScore();
				Destroy();
			}
		}
		else if (OtherActor->ActorHasTag("Ship") && Cast<APlayerShip>(OtherActor))
		{
			Cast<APlayerShip>(OtherActor)->ReceiveDamage(1.f);
			Destroy();
		}
	}
	
}
