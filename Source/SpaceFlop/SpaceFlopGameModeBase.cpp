// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SpaceFlopGameModeBase.h"

int ASpaceFlopGameModeBase::GetRandomNumber()
{
    srand(rand());
    return rand();
}