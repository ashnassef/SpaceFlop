// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceFlopGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPACEFLOP_API ASpaceFlopGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    static int GetRandomNumber();
};
