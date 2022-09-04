// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DMDGameModeBase.generated.h"

/**
 * Sets all controller classes for this game mode
 */
UCLASS()
class DYNAMICMAPDEMO_API ADMDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ADMDGameModeBase();
};
