// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ship.generated.h"

UCLASS()
class SPACEFLOP_API AShip : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Assets)
	class UBoxComponent* m_BoxCollider;

	UPROPERTY(EditAnywhere, Category = Assets)
        class UStaticMeshComponent* m_ShipBodyMesh;

    UPROPERTY(EditAnywhere, Category = Assets)
        class UStaticMeshComponent* m_ShipGlassMesh;

	UPROPERTY(EditAnywhere, Category = Assets)
	class UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, Category = Init)
	float m_ShipSpeed;

public:	
	// Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUp(float Value);

    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
