// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../ShipObjects/ShipObject.h"
#include "Thruster.h"
#include "Ship.generated.h"

UENUM()
enum TEMPLATES
{
    BUTTON          UMETA(DisplayName = BUTTON),
    SWITCH          UMETA(DisplayName = SWITCH),
    CHAIR           UMETA(DisplayName = CHAIR),
    SMALLCONSOLE    UMETA(DisplayName = SMALLCONSOLE),
    LARGECONSOLE    UMETA(DisplayName = LARGECONSOLE),
    BACKWALL        UMETA(DisplayName = BACKWALL)
};

UENUM()
enum THRUSTERS
{
    TOPRIGHT        UMETA(DisplayName = TOPRIGHT),
    TOPLEFT         UMETA(DisplayName = TOPLEFT),
    BOTTOMLEFT      UMETA(DisplayName = BOTTOMLEFT),
    BOTTOMRIGHT     UMETA(DisplayName = BOTTOMRIGHT)
};


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
        class UStaticMeshComponent* m_ShipBodyMesh;

    UPROPERTY(EditAnywhere, Category = Assets)
        class UStaticMeshComponent* m_ShipGlassMesh;

    UPROPERTY(EditAnywhere, Category = Assets)
        class UCameraComponent* m_Camera;

    UPROPERTY(EditAnywhere, Category = Assets)
        TArray<AThruster*> m_Thrusters;

    UPROPERTY(EditAnywhere, Category = Assets)
        TArray<APawn*> m_Astronauts;

    UPROPERTY(EditAnywhere, Category = Init)
        TSubclassOf<APawn> m_AstronautTemplate;

    UPROPERTY(EditAnywhere, Category = Init)
        float m_ShipSpeed;

    UPROPERTY(EditAnywhere, Category = Init)
        float m_RotationSpeed;

    UPROPERTY(EditAnywhere, Category = Init)
        TArray<TSubclassOf<AShipObject>> m_ShipObjectTemplates;

    UPROPERTY(EditAnywhere, Category = Init)
        TSubclassOf<AThruster> m_ThrusterTemplate;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual UPawnMovementComponent* GetMovementComponent() const override;

    void MoveUp(float Value);
    void Rotate(float Value);

    int GetDigitFromSocketName(FName Socket);

    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    class UShipMovementComponent* m_MovementComponent;

    bool bCanMove;

    float m_MovementDirection;

    bool bCanRotate;

    float m_Pitch;
    float m_Yaw;
    float m_Roll;
};
