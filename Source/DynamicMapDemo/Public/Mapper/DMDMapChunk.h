// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"

// Header for base class Actor
#include "GameFramework/Actor.h"
#include "DMDHexMetrics.h"
#include "DMDHexCell.h"

// Headers for all components ADMDMapChunk consists of
#include "Components/SceneComponent.h"
#include "ProceduralMeshComponent.h"

#include "DMDMapChunk.generated.h"

/**
 * Class defines a small chunk of map, consisted from a 
 * set of individual HexCells. Also this class handles 
 * all visuals (rendering) for its cells.
 * Full map (HexGrid) consists from a set of chunks.
 */
UCLASS(BlueprintType, Blueprintable)
class DYNAMICMAPDEMO_API ADMDMapChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMDMapChunk();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Scene component (root for ProceduralMesh for it to have Transform)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;  //Scene component (root for ProceduralMesh)
		
    // ProceduralMesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProceduralMeshComponent* ProceduralMeshPtr;  //ProceduralMesh component

	// ProceduralMesh data arrays
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh Data")
	TArray<FVector> Vertices;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh Data")
	TArray<int32> Triangles;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh Data")
	TArray<FVector> Normals;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh Data")
	TArray<FVector2D> UVs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh Data")
	TArray<FLinearColor> VertexLinearColors;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh Data")
	TArray<FProcMeshTangent> Tangents;

	// Clears procedural mesh data
	void ClearMeshData();

	// Creates procedural mesh
	void CreateMesh();

	// Recalculate mesh triangles data
	void TriangulateMesh();

	// Init chunk-related variables with boundaries check
	// It is a replacement for a parametrized constructor, 
	// prohibited in UE4
	void InitChunkVariables(FVector ChunkCoordinates);

protected:

	// Called when the game mode starts or when spawned
	virtual void BeginPlay() override;

	// Chunk global coordinates
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chunk Data")
	FVector GlobalChunkLocation
	{
		0.0f, 0.0f, 0.0f
	};

	// Linear array of this chunk cells. From left to right, from closest line to most far away.
	// In UE4 coords that means from y=0 to *ChunkSizeY, 
	// from x=0 to ChunkSizeX
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Elements")
	TArray<UDMDHexCell*> ChunkCells{};  //Linear array of UDMDHexCell* (this chunk cells)


private:
	// Watchdog to enforce InitChunkVariables() call
	// before any action with mesh can be permitted
	bool bWasInitialized = false;
};
