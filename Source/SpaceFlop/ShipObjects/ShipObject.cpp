// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipObject.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AShipObject::AShipObject()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    m_ShipObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    RootComponent = m_ShipObjectMesh;
}

