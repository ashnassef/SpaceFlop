// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Astronaut.generated.h"

UCLASS()
class SPACEFLOP_API AAstronaut : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAstronaut();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Assets)
		class USkeletalMeshComponent* m_SkeletalMesh;
};
