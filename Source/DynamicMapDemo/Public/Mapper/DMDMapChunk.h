// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"

// Header for base class Actor
#include "GameFramework/Actor.h"
#include "DMDHexMetrics.h"

// Headers for all components DMDMapChunk will consists of
#include "Components/SceneComponent.h"
#include "ProceduralMeshComponent.h"
#include "Engine/TextRenderActor.h"

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
	USceneComponent* ScenePtr;  //Scene component (root for ProceduralMesh)
		
    // ProceduralMesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProceduralMeshComponent* ProceduralMeshPtr;  //ProceduralMesh component

#if WITH_EDITOR  // Use more strict UE_BUILD_SHIPPING to check if Config==Shipping
	// Map chunk text labels are only available in editor,
	// so it must be enclosed with "#if WITH_EDITOR" before use
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<ATextRenderActor*> CoordTextActors {};  //Array of TextRenderActors
	//ATextRenderActor* TextRenderActorPtr = nullptr;  //TextRenderActor (contains private class UTextRenderComponent)
#endif

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
	//Property was used in deprecated function
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh Data")
	//TArray<FColor> VertexColors;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh Data")
	TArray<FProcMeshTangent> Tangents;

	// Clears procedural mesh data
	void ClearMeshData();

	// Creates procedural mesh
	void CreateMesh();

protected:
	// Chunk width (preferrably even integer)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chunk Metrics")
	int32 ChunkSizeX = 10;

	// Chunk height (preferrably even integer)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chunk Metrics")
	int32 ChunkSizeY = 10;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
