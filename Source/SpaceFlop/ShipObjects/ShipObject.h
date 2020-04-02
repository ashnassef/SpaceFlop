// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipObject.generated.h"

UCLASS()
class SPACEFLOP_API AShipObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipObject();

	UPROPERTY(EditAnywhere, Category = Assets)
	class UStaticMeshComponent* m_ShipObjectMesh;

};
