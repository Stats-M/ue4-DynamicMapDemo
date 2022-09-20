// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMDHexMetrics.h"
#include "DMDHexCell.h"
#include "DMDMapChunk.h"
#include "DMDHexGrid.generated.h"

/**
 * Class defines a hexagonal map, consisted from a set 
 * of small map chunks.
 */
UCLASS()
class DYNAMICMAPDEMO_API ADMDHexGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMDHexGrid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Amount of chunks (X) in the grid
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 ChunksX = 2;

	// Amount of chunks (Y) in the grid
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 ChunksY = 2;

	// Called when the game mode starts or when spawned
	virtual void BeginPlay() override;

};
