// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DMDHexMetrics.generated.h"


/**
 * Class that defines all metrics for game world. 
 * Most of them are static.
 */
UCLASS(BlueprintType)
class DYNAMICMAPDEMO_API UDMDHexMetrics : public UObject
{
	GENERATED_BODY()

public:
	UDMDHexMetrics();

	// Outer hex radius
	static const float OuterRadius;
	// Inner hex radius
	static const float InnerRadius;
	// Default coordinates of hex vertices in 3D
	static const TArray<FVector> HexMetrics3D;
	// Default coordinates of hex vertices in 2D
	static const TArray<FVector2D> HexMetrics2D;
};
