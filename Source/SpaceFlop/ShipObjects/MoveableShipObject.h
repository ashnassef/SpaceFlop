// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipObject.h"
#include "MoveableShipObject.generated.h"

/**
 * 
 */
UCLASS()
class SPACEFLOP_API AMoveableShipObject : public AShipObject
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMoveableShipObject();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;


public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
	
};
