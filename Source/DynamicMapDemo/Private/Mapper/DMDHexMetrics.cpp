// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#include "Mapper/DMDHexMetrics.h"

/**
 * Static members initialization 
 * (outside of any class definitions).
 */
const float UDMDHexMetrics::OuterRadius = 50.0f;

const float UDMDHexMetrics::InnerRadius = UDMDHexMetrics::OuterRadius * 0.866025404f;

const TArray<FVector> UDMDHexMetrics::HexMetrics3D =
{
    // Uses UE coordinates (Forward,Right,Up instead of X,Y,Z)
    // Counter clock-wise, starting from 12 hours
    FVector(UDMDHexMetrics::OuterRadius, 0.0f, 0.0f),
    FVector(0.5f * UDMDHexMetrics::OuterRadius, -UDMDHexMetrics::InnerRadius, 0.0f),
    FVector(-0.5f * UDMDHexMetrics::OuterRadius, -UDMDHexMetrics::InnerRadius, 0.0f),
    FVector(-UDMDHexMetrics::OuterRadius, 0.0f, 0.0f),
    FVector(-0.5f * UDMDHexMetrics::OuterRadius, UDMDHexMetrics::InnerRadius, 0.0f),
    FVector(0.5f * UDMDHexMetrics::OuterRadius, UDMDHexMetrics::InnerRadius, 0.0f),
    FVector(UDMDHexMetrics::OuterRadius, 0.0f, 0.0f)  // last vertice repeats the first one
};

const TArray<FVector2D> UDMDHexMetrics::HexMetrics2D =
{
    // Uses UE coordinates (Forward,Right,Up instead of X,Y,Z)
    // Counter clock-wise, starting from 12 hours
    FVector2D(UDMDHexMetrics::OuterRadius, 0.0f),
    FVector2D(0.5f * UDMDHexMetrics::OuterRadius, -UDMDHexMetrics::InnerRadius),
    FVector2D(-0.5f * UDMDHexMetrics::OuterRadius, -UDMDHexMetrics::InnerRadius),
    FVector2D(-UDMDHexMetrics::OuterRadius, 0.0f),
    FVector2D(-0.5f * UDMDHexMetrics::OuterRadius, UDMDHexMetrics::InnerRadius),
    FVector2D(0.5f * UDMDHexMetrics::OuterRadius, UDMDHexMetrics::InnerRadius),
    FVector2D(UDMDHexMetrics::OuterRadius, 0.0f)  // last vertice repeats the first one
};

const int32 UDMDHexMetrics::TotalChunksCountHeightMax = 20;

const int32 UDMDHexMetrics::TotalChunksCountWidthMax = 20;

const int32 UDMDHexMetrics::ChunkSizeHeightMax = 8;

const int32 UDMDHexMetrics::ChunkSizeWidthMax = 8;

UDMDHexMetrics::UDMDHexMetrics()
{}