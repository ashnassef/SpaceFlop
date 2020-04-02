// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipMovementComponent.h"

void UShipMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    FVector DesriredMovementThisFrame = ConsumeInputVector() * DeltaTime * 150.0f;

    if (!DesriredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesriredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        if (Hit.IsValidBlockingHit())
        {
            SlideAlongSurface(DesriredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
        }
    }
}
