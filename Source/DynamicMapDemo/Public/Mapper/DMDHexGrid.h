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
UCLASS()
class DYNAMICMAPDEMO_API ADMDHexGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMDHexGrid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Scene component (root for ProceduralMesh for it to have Transform)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* ScenePtr;  //Scene component (root for ProceduralMesh)

#if !UE_BUILD_SHIPPING  // Use more strict than WITH_EDITOR check (project Config==Shipping)
	// Map chunk text labels are only available in editor,
	// so it must be enclosed with "#if WITH_EDITOR" or UE_BUILD_SHIPPING before use
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<ATextRenderActor*> CoordTextActors{};  //Array of TextRenderActors (contains private class UTextRenderComponent)
#endif

protected:
	// Amount of chunks (X) in the grid
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 ChunksX = 2;

	// Amount of chunks (Y) in the grid
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid Metrics")
	int32 ChunksY = 2;

	// Chunk width (preferrably even integer)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chunk Metrics")
	int32 ChunkSizeX = 5;

	// Chunk height (preferrably even integer)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chunk Metrics")
	int32 ChunkSizeY = 5;

	// Called when the game mode starts or when spawned
	virtual void BeginPlay() override;

};
