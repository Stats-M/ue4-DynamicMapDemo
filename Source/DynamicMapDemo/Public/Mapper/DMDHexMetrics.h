// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DMDHexMetrics.generated.h"

/**
 * A Struct to hold vertices coordinates of 1U hex.
 */
USTRUCT(BlueprintType)
struct FHexVertices
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Corners")
	FVector Corner1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Corners")
	FVector Corner2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Corners")
	FVector Corner3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Corners")
	FVector Corner4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Corners")
	FVector Corner5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex Corners")
	FVector Corner6;
};

/**
 * Class that defines all metrics for game world.
 */
UCLASS(BlueprintType)
class DYNAMICMAPDEMO_API UDMDHexMetrics : public UObject
{
	GENERATED_BODY()

public:
	UDMDHexMetrics();

public:
	// Outer radius for pointy side up hexagon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hex Metrics")
	float OuterRadius = 10.0f;

	// Inner radius for pointy side up hexagon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hex Metrics")
	float InnerRadius = OuterRadius * 0.866025404f;
	
	// Default hex vertices coordinates (ratio for 1U hex)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hex Metrics")
	FHexVertices DefaultHexVertices;

};
