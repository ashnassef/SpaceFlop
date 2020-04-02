// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionableShipObject.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AActionableShipObject::AActionableShipObject()
{
    m_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
    m_SkeletalMesh->SetupAttachment(RootComponent);
}
void AActionableShipObject::BeginPlay()
{
    Super::BeginPlay();
}

void AActionableShipObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
