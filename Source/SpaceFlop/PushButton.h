// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushButton.generated.h"

UCLASS()
class SPACEFLOP_API APushButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APushButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = Assets)
        class UBoxComponent* m_BoxCollider;

    UPROPERTY(EditAnywhere, Category = Assets)
        class UStaticMeshComponent* m_ButtonBaseMesh;

    UPROPERTY(EditAnywhere, Category = Assets)
        class UStaticMeshComponent* m_ButtonMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};