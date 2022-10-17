// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "DMDHexMetrics.h"
#include "DMDHexCell.h"
#include "DMDMapChunk.h"

// Headers for all components ADMDHexGrid consists of
#include "Components/SceneComponent.h"
#include "ProceduralMeshComponent.h"
#include "Components/TextRenderComponent.h"      // TextRender Component for text data manipulations
#include "Engine/TextRenderActor.h"              // TextRender Actor (contains UTextRenderComponent) with transform

#include "DMDHexGrid.generated.h"

/**
 * Class defines a hexagonal map, consisted from a set 
 * of small map chunks (each one with ProceduralMesh actor).
 * Contains:
 *  - all text labels for all chunks
 *  - all cells data (chunks get pointers to them)
 */
UCLASS(BlueprintType, Blueprintable)
class DYNAMICMAPDEMO_API ADMDHexGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMDHexGrid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Scene component (root component) (for having Transform properties)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Components")
	USceneComponent* Scene;  //Scene component

#if !UE_BUILD_SHIPPING  // (UE_BUILD_SHIPPING - project Config==Shipping)
	// Map chunk text labels are only available in editor,
	// so it must be enclosed with "#if WITH_EDITOR" or UE_BUILD_SHIPPING before use
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") - incompare with #if...#endif
	TArray<ATextRenderActor*> CoordTextActors{};  //Array of TextRenderActors (contains private class UTextRenderComponent)
#endif

	// Defines origin location for text labels
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	FVector LabelsStartLocation
	{
		-200.0f, -200.0f, 5.0f
	};

	// Amount of chunks in the grid (grid width)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 TotalChunksCountWidth = 1;

	// Amount of chunks in the grid (grid height)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 TotalChunksCountHeight = 1;

	// Chunk height (number of hexes) (even integer)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 ChunkSizeHeight = 6;

	// Chunk width (number of hexes) (even integer)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 ChunkSizeWidth = 6;

	// Defines origin location for grid
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	FVector GridStartLocation
	{
		-200.0f, -200.0f, 0.0f
	};

	// Font size for grid labels
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	float LabelFontSize = 24.0f;

	// Creates a cell instance and adds it to cell array(s)
    // X,Y,Z are cell's indexes in rectangular 3D array
	void CreateCell(int32 X, int32 Y, int32 Z);

protected:
	// Called when the game mode starts or when spawned
	virtual void BeginPlay() override;

	// Linear array of spawned map chunks. From left to right, from closest line to most far away.
	// In UE4 coords that means from y=0 to TotalChunkCountWidth, from x=0 to TotalChunkCountHeight
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Elements")
	TArray<ADMDMapChunk*> MapChunks{};  //Linear array of DMDMapChunk* (map chunks)

	// Linear array of map cells. From left to right, from closest line to most far away.
	// In UE4 coords that means from y=0 to TotalChunkCountWidth*ChunkSizeWidth, 
	// from x=0 to TotalChunkCountHeight*ChunkSizeHeight
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Elements")
	TArray<UDMDHexCell*> GridCells{};  //Linear array of UDMDHexCell* (map cells)

private:
	// Total cells count (width)
	int32 cellsTotalCountWidth = 0;
	// Total cells count (height)
	int32 cellsTotalCountHeight = 0;
	// Total cells on map
	int32 cellsCountTotal = 0;
	// Total chunks on map
	int32 chunksCountTotal = 0;

	// Init grid-related variables with boundaries check
	// (to be called in BeginPlay())
	void InitGridVariables();


// ***** TESTS SECTION *****
// Functions used for testing
// can replace guards with #if !UE_BUILD_SHIPPING instead
#if WITH_DEV_AUTOMATION_TESTS
public:
	void DummyInitVariables()
	{
		InitGridVariables();
	};
	int32 GetCellsTotalCountWidth() const
	{
		return cellsTotalCountWidth;
	};
	int32 GetCellsTotalCountHeight() const
	{
		return cellsTotalCountHeight;
	};
#endif

};