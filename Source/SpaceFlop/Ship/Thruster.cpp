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
    for (int i = 0; i < m_ParticleSystemComponents.Num(); i++)
    {
        m_ParticleSystemComponents[i] = UGameplayStatics::SpawnEmitterAttached(m_ParticleSystem,
                                                                               m_Mesh,
                                                                               m_Mesh->GetAllSocketNames()[i],
                                                                               FVector::ZeroVector,
                                                                               FRotator::ZeroRotator,
                                                                               EAttachLocation::SnapToTarget);
    }
}

// Called every frame
void AThruster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AThruster::ToggleParticleSystem(bool bIsActive)
{
    for (UParticleSystemComponent* ParticleSystemComponent : m_ParticleSystemComponents)
    {
        bIsActive ? ParticleSystemComponent->ActivateSystem() : ParticleSystemComponent->DeactivateSystem();
        ParticleSystemComponent->Activate(bIsActive);
    }
}

TArray<UParticleSystemComponent*> AThruster::GetParticleSystemComponents()
{
    return TArray<UParticleSystemComponent*>();
}

