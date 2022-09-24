// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#include "Mapper/DMDHexMetrics.h"

/**
 * Static members initialization 
 * (outside of any class definitions).
 */
const float UDMDHexMetrics::OuterRadius = 100.0f;

const float UDMDHexMetrics::InnerRadius = UDMDHexMetrics::OuterRadius * 0.866025404f;

const TArray<FVector> UDMDHexMetrics::HexMetrics3D =
{
    FVector(0.0f, UDMDHexMetrics::OuterRadius, 0.0f),
    FVector(UDMDHexMetrics::InnerRadius, 0.5f * UDMDHexMetrics::OuterRadius, 0.0f),
    FVector(UDMDHexMetrics::InnerRadius, -0.5f * UDMDHexMetrics::OuterRadius, 0.0f),
    FVector(0.0f, -UDMDHexMetrics::OuterRadius, 0.0f),
    FVector(-UDMDHexMetrics::InnerRadius, -0.5f * UDMDHexMetrics::OuterRadius, 0.0f),
    FVector(-UDMDHexMetrics::InnerRadius, 0.5f * UDMDHexMetrics::OuterRadius, 0.0f),
    FVector(0.0f, UDMDHexMetrics::OuterRadius, 0.0f)  // last vertice repeats the first one
};

const TArray<FVector2D> UDMDHexMetrics::HexMetrics2D =
{
    FVector2D(0.0f, UDMDHexMetrics::OuterRadius),
    FVector2D(UDMDHexMetrics::InnerRadius, 0.5f * UDMDHexMetrics::OuterRadius),
    FVector2D(UDMDHexMetrics::InnerRadius, -0.5f * UDMDHexMetrics::OuterRadius),
    FVector2D(0.0f, -UDMDHexMetrics::OuterRadius),
    FVector2D(-UDMDHexMetrics::InnerRadius, -0.5f * UDMDHexMetrics::OuterRadius),
    FVector2D(-UDMDHexMetrics::InnerRadius, 0.5f * UDMDHexMetrics::OuterRadius),
    FVector2D(0.0f, UDMDHexMetrics::OuterRadius)  // last vertice repeats the first one
};

const int32 UDMDHexMetrics::ChunksAmountXMax = 25;

const int32 UDMDHexMetrics::ChunksAmountYMax = 20;

const int32 UDMDHexMetrics::ChunkSizeXMax = 8;

const int32 UDMDHexMetrics::ChunkSizeYMax = 8;

UDMDHexMetrics::UDMDHexMetrics()
{}