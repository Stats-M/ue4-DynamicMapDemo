// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev


#include "Mapper/DMDHexMetrics.h"

UDMDHexMetrics::UDMDHexMetrics()
{
    DefaultHexVertices.Corner1 = FVector(0.0f, 0.0f, OuterRadius);
    DefaultHexVertices.Corner2 = FVector(InnerRadius, 0.0f, 0.5f * OuterRadius);
    DefaultHexVertices.Corner3 = FVector(InnerRadius, 0.0f, -0.5f * OuterRadius);
    DefaultHexVertices.Corner4 = FVector(0.0f, 0.0f, -OuterRadius);
    DefaultHexVertices.Corner5 = FVector(-InnerRadius, 0.0f, -0.5f * OuterRadius);
    DefaultHexVertices.Corner6 = FVector(-InnerRadius, 0.0f, 0.5f * OuterRadius);
}