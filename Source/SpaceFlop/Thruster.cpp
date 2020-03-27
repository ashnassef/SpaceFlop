// Fill out your copyright notice in the Description page of Project Settings.


#include "Thruster.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AThruster::AThruster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ThrusterMesh = CreateDefaultSubobject<UStaticMeshComponent>("Thruster Mesh");
	RootComponent = m_ThrusterMesh;
	
	m_ParticleEmitter = CreateDefaultSubobject<UParticleSystemComponent>("Particle Emitter");
}

// Called when the game starts or when spawned
void AThruster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThruster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThruster::FireThruster(bool IsFiring)
{
	// Activate or deactivate the particle emitter.
	IsFiring ? m_ParticleEmitter->ActivateSystem() : m_ParticleEmitter->DeactivateSystem();
}

