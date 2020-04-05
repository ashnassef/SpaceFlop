// Fill out your copyright notice in the Description page of Project Settings.


#include "Thruster.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AThruster::AThruster()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    RootComponent = m_Mesh;

    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/Assets/Particles/ThrusterFire.ThrusterFire'"));
    if (ParticleSystem.Succeeded())
    {
        m_ParticleSystem = ParticleSystem.Object;
    }
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

void AThruster::ToggleParticleSystem(bool bIsActive, bool bNear, bool bFar)
{
    for (int i = 0; i < m_ParticleSystemComponents.Num(); i++)
    {
        if (bNear && i != 0)
        {
            continue;
        }
        if (bFar && i != 2)
        {
            continue;
        }
        if (bIsActive)
        {
            m_ParticleSystemComponents[i]->Activate();
        }
        else
        {
            m_ParticleSystemComponents[i]->Deactivate();
        }
    }
}

UParticleSystem* AThruster::GetParticleSystem()
{
    return m_ParticleSystem;
}

TArray<UParticleSystemComponent*> AThruster::GetParticleSystemComponents()
{
    return m_ParticleSystemComponents;
}

