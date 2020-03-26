// Fill out your copyright notice in the Description page of Project Settings.


#include "PushButton.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APushButton::APushButton()
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
void APushButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APushButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APushButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

