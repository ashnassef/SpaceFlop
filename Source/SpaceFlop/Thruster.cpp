// Fill out your copyright notice in the Description page of Project Settings.


#include "Thruster.h"

// Sets default values
AThruster::AThruster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

