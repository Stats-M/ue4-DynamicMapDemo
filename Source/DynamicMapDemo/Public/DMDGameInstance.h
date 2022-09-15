// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DMDGameInstance.generated.h"

/**
 * GameInstance: high-level manager object for an instance of the running game. 
 * Spawned at game creation and not destroyed until game instance is shut down. 
 * Running as a standalone game, there will be one of these. 
 * Running in PIE (play-in-editor) will generate one of these per PIE instance.
 * Used for storing global settings and data, not related to a Level/GameMode.
 * 
 * Access via UWorld: GetWorld()->GetGameInstance<UDMDGameInstance>()->...
 */
UCLASS()
class DYNAMICMAPDEMO_API UDMDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
};
