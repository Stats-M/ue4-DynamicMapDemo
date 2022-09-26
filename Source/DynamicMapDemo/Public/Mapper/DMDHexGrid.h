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
 * of small map chunks.
 * Contains:
 *  - all text labels for all chunks
 *  - all cells data
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

	// Scene component (root for ProceduralMesh for it to have Transform)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Components")
	USceneComponent* ScenePtr;  //Scene component (root for ProceduralMesh)

#if !UE_BUILD_SHIPPING  // (UE_BUILD_SHIPPING - project Config==Shipping)
	// Map chunk text labels are only available in editor,
	// so it must be enclosed with "#if WITH_EDITOR" or UE_BUILD_SHIPPING before use
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") - incompare with #if...#endif
	TArray<ATextRenderActor*> CoordTextActors{};  //Array of TextRenderActors (contains private class UTextRenderComponent)
#endif

	// Set start text labels location (origin)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	FVector LabelsStartLocation
	{
		-200.0f, -200.0f, 5.0f
	};

	// Amount of chunks in the grid (grid width)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 ChunksAmountX = 1;

	// Amount of chunks in the grid (grid height)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 ChunksAmountY = 1;

	// Chunk width (preferrably even integer)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 ChunkSizeX = 5;

	// Chunk height (preferrably even integer)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 ChunkSizeY = 5;

	// Set start actor location (oriin)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	FVector GridStartLocation
	{
		-600.0f, -600.0f, 0.0f
	};

protected:
	// Called when the game mode starts or when spawned
	virtual void BeginPlay() override;

	// Linear array of spawned map chunks. From left to right, from closest line to most far away.
	// In UE4 coords that means from y=0 to ChunksAmountY, from x=0 to ChunksAmountX
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Elements")
	TArray<ADMDMapChunk*> MapChunkActors{};  //Linear array of DMDMapChunk* (map chunks)

	// Linear array of map cells. From left to right, from closest line to most far away.
	// In UE4 coords that means from y=0 to ChunksAmountY*ChunkSizeY, 
	// from x=0 to ChunksAmountX*ChunkSizeX
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Elements")
	TArray<UDMDHexCell*> GridCells{};  //Linear array of UDMDHexCell* (map cells)

	// Font size for grid labels
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	float LabelFontSize = 24.0f;

private:
	// Total cells count (width)
	int32 cellsCountX = 0;
	// Total cells count (height)
	int32 cellsCountY = 0;
	// Total cells on map
	int32 cellsCountTotal = 0;
	// Total chunks on map
	int32 chunksCountTotal = 0;

	// Init grid-related variables with boundaries check
	void InitGridVariables();
};