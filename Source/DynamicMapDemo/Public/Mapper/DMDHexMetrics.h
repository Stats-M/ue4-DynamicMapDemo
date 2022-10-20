// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DMDHexMetrics.generated.h"

/**
 * Class that defines all metrics for game map. 
 * Most of them are static.
 */
UCLASS(BlueprintType)
class DYNAMICMAPDEMO_API UDMDHexMetrics : public UObject
{
	GENERATED_BODY()

public:
	UDMDHexMetrics();

	// Vertices count for a grid cell
	static const int32 CellVerticesCount;

	// Outer hex radius in UE Units. The root value for all others metrics.
	static const float OuterRadius;
	// Inner hex radius
	static const float InnerRadius;
	// Default coordinates of hex vertices in 3D (Counter Clock-wise)
	static const TArray<FVector> HexMetrics3D;
	// Default coordinates of hex vertices in 2D (Counter Clock-wise)
	static const TArray<FVector2D> HexMetrics2D;

	// Maximum chunks amount in the map (map height)
	static const int32 TotalChunksCountHeightMax;
	// Maximum chunks amount in the map (map width)
	static const int32 TotalChunksCountWidthMax;
	// Maximum single chunk height (along UE Forward (X) axis)
	static const int32 ChunkSizeHeightMax;
	// Maximum single chunk width (along UE Right (Y) axis)
	static const int32 ChunkSizeWidthMax;
};
