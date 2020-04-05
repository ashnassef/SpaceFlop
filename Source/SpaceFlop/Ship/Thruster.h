// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Assets)
        class UStaticMeshComponent* m_Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Assets)
        class UParticleSystem* m_ParticleSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Assets)
        TArray<UParticleSystemComponent*> m_ParticleSystemComponents;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Effects)
		void ToggleParticleSystem(bool bIsActive, bool bNear = false, bool bFar = false);

	UFUNCTION(BlueprintCallable, Category = Effects)
		UParticleSystem* GetParticleSystem();

	UFUNCTION(BlueprintCallable, Category = Effects)
		TArray<UParticleSystemComponent*> GetParticleSystemComponents();
};
