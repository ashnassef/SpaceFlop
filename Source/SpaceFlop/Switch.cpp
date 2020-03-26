// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASwitch::ASwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    m_BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
    RootComponent = m_BoxCollider;

    m_ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Button Mesh");
    m_ButtonMesh->SetupAttachment(RootComponent);

    m_ButtonBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Button Base Mesh");
    m_ButtonBaseMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

