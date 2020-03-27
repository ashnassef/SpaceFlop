// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Thruster.generated.h"

UCLASS()
class SPACEFLOP_API AThruster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThruster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Assets)
	class UStaticMeshComponent* m_ThrusterMesh;

	UPROPERTY(EditAnywhere, Category = Assets)
	class UParticleSystemComponent* m_ParticleEmitter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void FireThruster(bool IsFiring);

};
