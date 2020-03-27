// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"

#define PrintGreen(text, val) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(text, val))
#define PrintRed(text, val) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(text, val))

// Sets default values
AShip::AShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	RootComponent = m_Camera;

	m_BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	m_BoxCollider->SetSimulatePhysics(true);
	m_BoxCollider->SetEnableGravity(false);
	m_BoxCollider->SetupAttachment(RootComponent);

	m_ShipBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ship Body Mesh");
    m_ShipBodyMesh->SetupAttachment(m_BoxCollider);

    m_ShipGlassMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ship Glass Mesh");
    m_ShipGlassMesh->SetupAttachment(m_ShipBodyMesh);

	m_ShipSpeed = 5000.0f;
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_BoxCollider->GetRelativeLocation().Z > 930.0f)
	{
		m_BoxCollider->GetBodyInstance()->ClearForces(true);
		m_BoxCollider->GetBodyInstance()->SetLinearVelocity(FVector::ZeroVector, false);
		m_BoxCollider->SetRelativeLocation(FVector(m_BoxCollider->GetRelativeLocation().X, m_BoxCollider->GetRelativeLocation().Y, 930.0f));
	}

    if (m_BoxCollider->GetRelativeLocation().Z < -930.0f)
    {
        m_BoxCollider->GetBodyInstance()->ClearForces(true);
        m_BoxCollider->GetBodyInstance()->SetLinearVelocity(FVector::ZeroVector, false);
        m_BoxCollider->SetRelativeLocation(FVector(m_BoxCollider->GetRelativeLocation().X, m_BoxCollider->GetRelativeLocation().Y, -930.0f));
    }
}

void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveUp", this, &AShip::MoveUp);
}

void AShip::MoveUp(float Value)
{
	if (Value > 0 && m_BoxCollider->GetRelativeLocation().Z < 930.0f)
	{
        m_BoxCollider->GetBodyInstance()->AddImpulse(FVector::UpVector * m_ShipSpeed, true);
        PrintGreen(TEXT("Relative Z Location: %f"), m_BoxCollider->GetRelativeLocation().Z);
	}
	
	if (Value < 0 && m_BoxCollider->GetRelativeLocation().Z > -930.0f)
	{
		m_BoxCollider->GetBodyInstance()->AddImpulse(FVector::UpVector * -m_ShipSpeed, true);
        PrintGreen(TEXT("Relative Z Location: %f"), m_BoxCollider->GetRelativeLocation().Z);
    }
}

void AShip::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("LooseObject"))
	{

	}
}

