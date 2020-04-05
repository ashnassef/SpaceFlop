// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "ShipMovementComponent.h"
#include "../ShipObjects/ActionableShipObject.h"
#include "../ShipObjects/MoveableShipObject.h"
#include "../ShipObjects/StationaryShipObject.h"
#include "../SpaceFlopGameModeBase.h"

#define PrintGreen(text, val) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT(text), val))
#define PrintRed(text, val) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT(text), val))

// Sets default values
AShip::AShip()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

#pragma region Components
    // Initialize components
    m_ShipBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ship Body Mesh");
    RootComponent = m_ShipBodyMesh;

    m_ShipGlassMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ship Glass Mesh");
    m_ShipGlassMesh->SetupAttachment(m_ShipBodyMesh);

    m_Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

    m_MovementComponent = CreateDefaultSubobject<UShipMovementComponent>("Pawn Movement Component");
    m_MovementComponent->UpdatedComponent = RootComponent;
#pragma endregion

#pragma region Init Variables
    m_ShipSpeed = 20.0f;
    m_RotationSpeed = 10.0f;
    m_MovementDirection = 0;
    bCanMove = true;
    bCanRoll = false;
    bCanPitch = false;
    bCanYaw = false;

    m_Pitch = 0;
    m_Yaw = 0;
    m_Roll = 0;
#pragma endregion
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
    Super::BeginPlay();

    TArray<FName> Sockets = GetRootComponent()->GetAllSocketNames();

    for (FName Socket : Sockets)
    {
        // Skip these sockets
        if (Socket.ToString().Contains("_1") || Socket.ToString().Contains("_2") || Socket.ToString().Contains("SpawningPoint"))
        {
            continue;
        }
        // Spawn Thrusters
        if (Socket.ToString().Contains("Thruster"))
        {
            AThruster* Thruster = GetWorld()->SpawnActor<AThruster>(m_ThrusterTemplate, FVector::ZeroVector, FRotator::ZeroRotator);
            Thruster->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
            m_Thrusters.Add(Thruster);
        }
        // Spawn Consoles, Chairs, Buttons, and Switches
        if (Socket.ToString().Contains("Console") && ASpaceFlopGameModeBase::GetRandomNumber() % 2)
        {
            int SSO_Template = (ASpaceFlopGameModeBase::GetRandomNumber() % 2) + 3;
            AStationaryShipObject* SSO_Console = GetWorld()->SpawnActor<AStationaryShipObject>(m_ShipObjectTemplates[SSO_Template], FVector::ZeroVector, FRotator::ZeroRotator);
            SSO_Console->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);

            AStationaryShipObject* SSO_Chair = GetWorld()->SpawnActor<AStationaryShipObject>(m_ShipObjectTemplates[CHAIR], FVector::ZeroVector, FRotator::ZeroRotator);
            FName Chair_Socket = *("Socket_Chair" + FString::FromInt(GetDigitFromSocketName(Socket)));
            SSO_Chair->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Chair_Socket);
            m_UsedSockets.Add(Chair_Socket);

            if (SSO_Template == SMALLCONSOLE)
            {
                int ASO_Template = ASpaceFlopGameModeBase::GetRandomNumber() % 2;
                AActionableShipObject* ASO = GetWorld()->SpawnActor<AActionableShipObject>(m_ShipObjectTemplates[ASO_Template], FVector::ZeroVector, FRotator::ZeroRotator);
                FString ASO_String = Socket.ToString() + "_1S";
                FName ASO_Socket = FName(*ASO_String);
                ASO->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, ASO_Socket);
            }
            else if (SSO_Template == LARGECONSOLE)
            {
                int ASO1_Template = ASpaceFlopGameModeBase::GetRandomNumber() % 2;
                int ASO2_Template = ASpaceFlopGameModeBase::GetRandomNumber() % 2;

                FString ASO1_String = Socket.ToString() + "_1L";
                FName ASO1_Socket = FName(*ASO1_String);
                AActionableShipObject* ASO1 = GetWorld()->SpawnActor<AActionableShipObject>(m_ShipObjectTemplates[ASO1_Template], m_ShipBodyMesh->GetSocketLocation(ASO1_Socket), FRotator::ZeroRotator);
                ASO1->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, ASO1_Socket);

                FString ASO2_String = Socket.ToString() + "_2L";
                FName ASO2_Socket = FName(*ASO2_String);
                AActionableShipObject* ASO2 = GetWorld()->SpawnActor<AActionableShipObject>(m_ShipObjectTemplates[ASO2_Template], m_ShipBodyMesh->GetSocketLocation(ASO2_Socket), FRotator::ZeroRotator);
                ASO2->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, ASO2_Socket);
            }
        }
        // Spawn more Buttons and Switches
        if (Socket.ToString().Contains("Replicator") && ASpaceFlopGameModeBase::GetRandomNumber() % 2)
        {
            int ASO_Template = ASpaceFlopGameModeBase::GetRandomNumber() % 2;
            AActionableShipObject* ASO = GetWorld()->SpawnActor<AActionableShipObject>(m_ShipObjectTemplates[ASO_Template], FVector::ZeroVector, FRotator::ZeroRotator);
            ASO->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
        }
        // Spawn BackWall
        if (Socket.ToString().Contains("BackWall"))
        {
            AStationaryShipObject* SSO = GetWorld()->SpawnActor<AStationaryShipObject>(m_ShipObjectTemplates[BACKWALL], FVector::ZeroVector, FRotator::ZeroRotator);
            SSO->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
        }
    }
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (m_UsedSockets.Num())
    {
        SpawnAstronaut(m_UsedSockets[0]);
    }
    // Turn off thrusters when you aren't using them. Use fuel responsibly!
    if (!bCanRoll && !bCanPitch && !bCanYaw && !bCanMove && m_Thrusters.Num() > 0)
    {
        ToggleThrusters();
    }

    // Vertical movement update
    if (bCanMove)
    {
        m_MovementComponent->AddInputVector(FVector(0, 0, m_ShipSpeed * m_MovementDirection), true);
        bCanMove = false;
    }

    // Rotation update
    if (bCanRoll)
    {
        FRotator newRotation = FRotator(0, 0, m_Roll);
        AddActorLocalRotation(newRotation, true);
        bCanRoll = false;
    }
    if (bCanPitch)
    {
        FRotator newRotation = FRotator(m_Pitch, 0, 0);
        AddActorLocalRotation(newRotation, true);
        bCanPitch = false;
    }
}

void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveUp", this, &AShip::MoveUp);
    PlayerInputComponent->BindAxis("Roll", this, &AShip::Roll);
    PlayerInputComponent->BindAxis("Pitch", this, &AShip::Pitch);
}

UPawnMovementComponent* AShip::GetMovementComponent() const
{
    return m_MovementComponent;
}

void AShip::MoveUp(float Value)
{
    if (m_MovementComponent && m_MovementComponent->UpdatedComponent == RootComponent)
    {
        // Limit vertical movement
        if (GetActorLocation().Z < 900.0f && Value > 0)
        {
            m_MovementDirection = Value;

            ToggleThrusters(false, false, true, true);

            bCanMove = true;
        }

        if (GetActorLocation().Z > -900.0f && Value < 0)
        {
            m_MovementDirection = Value;

            ToggleThrusters(true, true, false, false);

            bCanMove = true;
        }
    }
}

void AShip::Roll(float Value)
{
    if (m_MovementComponent && m_MovementComponent->UpdatedComponent == RootComponent)
    {
        // Limit rotation about X-axis
        if (GetActorRotation().Roll < 25.0f && Value > 0)
        {
            m_Roll = m_RotationSpeed * Value;

            ToggleThrusters(true, false, true, false);

            bCanRoll = true;
        }

        if (GetActorRotation().Roll > -21.0f && Value < 0)
        {
            m_Roll = m_RotationSpeed * Value;

            ToggleThrusters(false, true, false, true);

            bCanRoll = true;
        }
    }
}

void AShip::Pitch(float Value)
{
    if (m_MovementComponent && m_MovementComponent->UpdatedComponent == RootComponent)
    {
        // Limit rotation about the Y axis
        if (GetActorRotation().Pitch < 15.0f && Value > 0)
        {
            m_Pitch = m_RotationSpeed * Value * 0.75f;

            ToggleThrusters(true, true, true, true, true, false);

            bCanPitch = true;
        }

        if (GetActorRotation().Pitch > -15.0f && Value < 0)
        {
            m_Pitch = m_RotationSpeed * Value * 0.75f;

            ToggleThrusters(true, true, true, true, false, true);

            bCanPitch = true;
        }
    }
}

int AShip::GetDigitFromSocketName(FName Socket)
{
    if (Socket.ToString().Contains("1"))
    {
        return 1;
    }
    if (Socket.ToString().Contains("2"))
    {
        return 2;
    }
    if (Socket.ToString().Contains("3"))
    {
        return 3;
    }
    if (Socket.ToString().Contains("4"))
    {
        return 4;
    }
    if (Socket.ToString().Contains("5"))
    {
        return 5;
    }
    if (Socket.ToString().Contains("6"))
    {
        return 6;
    }

    return 0;
}

void AShip::ToggleThrusters(bool TopRight, bool TopLeft, bool BottomLeft, bool BottomRight, bool Near, bool Far)
{
    m_Thrusters[TOPRIGHT]->ToggleParticleSystem(TopRight, Near, Far);
    m_Thrusters[TOPLEFT]->ToggleParticleSystem(TopLeft, Near, Far);
    m_Thrusters[BOTTOMLEFT]->ToggleParticleSystem(BottomLeft, Near, Far);
    m_Thrusters[BOTTOMRIGHT]->ToggleParticleSystem(BottomRight, Near, Far);
}

void AShip::SpawnAstronaut(FName Socket)
{
    APawn* Astronaut = GetWorld()->SpawnActor<APawn>(m_AstronautTemplate, FVector(0, 130.0f, 215.0f), FRotator::ZeroRotator);
    if (Astronaut)
    {
        m_Astronauts.Add(Astronaut);
        Astronaut->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
        Astronaut->SetOwner(this);
        m_UsedSockets.Remove(Socket);
    }
}

void AShip::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("LooseObject"))
    {

    }
}

