// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AShip::AShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	RootComponent = m_BoxCollider;

	m_ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ship Mesh");
	m_ShipMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShip::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

