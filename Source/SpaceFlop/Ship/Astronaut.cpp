// Fill out your copyright notice in the Description page of Project Settings.


#include "Astronaut.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AAstronaut::AAstronaut()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	m_SkeletalMesh->SetSimulatePhysics(true);
	RootComponent = m_SkeletalMesh;
}

