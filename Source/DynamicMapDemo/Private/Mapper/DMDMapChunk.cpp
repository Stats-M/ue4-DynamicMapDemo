// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#include "Mapper/DMDMapChunk.h"

DEFINE_LOG_CATEGORY_STATIC(LogHexGrid, All, All)

// Sets default values
ADMDMapChunk::ADMDMapChunk()
{
	UE_LOG(LogHexGrid, Display, TEXT("ADMDMapChunk constructor"));
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject is preferred over AttachToComponent.
	// Argument - component name that will be used by UE
	// (it is not the same as displayed name of parent class).
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	ProceduralMeshPtr = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshChunk"));

	// Setting up hierarchy
	// 1. Setting the root component for AActor
	RootComponent = Scene;
	Scene->bUseAttachParentBound = true;  // Use parent actor bounds instead of its own (optimization)
	// 2. Setting subcomponents
	ProceduralMeshPtr->SetupAttachment(Scene);
}

// Called when the game mode starts or when spawned
void ADMDMapChunk::BeginPlay()
{
	Super::BeginPlay();
	
	ClearMeshData();

	CreateMesh();
}

void ADMDMapChunk::InitChunkVariables(FVector ChunkCoordinates)
{
	// Save global chunk coordinates origin
	GlobalChunkLocation = ChunkCoordinates;

	// Initialization was done. May proceed further
	bWasInitialized = true;
}

// Called every frame
void ADMDMapChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADMDMapChunk::ClearMeshData()
{
	// Clear all mesh data arrays
	Vertices.Empty();
	Triangles.Empty();
	UVs.Empty();
	Normals.Empty();
	VertexLinearColors.Empty();
	Tangents.Empty();
}

void ADMDMapChunk::CreateMesh()
{
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 5; ++y)
		{
			// 1. Vertices of a squad
			Vertices.Add(FVector(-200.0f + x * 200.0f, -200.0f + y * 200.0f, 0.0f));
			Vertices.Add(FVector(-200.0f + x * 200.0f, -200.0f + (y + 1) * 200.0f, 0.0f));
			Vertices.Add(FVector(-200.0f + (x + 1) * 200.0f, -200.0f + (y + 1) * 200.0f, 0.0f));
			Vertices.Add(FVector(-200.0f + (x + 1) * 200.0f, -200.0f + y * 200.0f, 0.0f));

			// 2. Triangles
			Triangles.Add(0 + (x * 20) + y * 4);
			Triangles.Add(1 + (x * 20) + y * 4);
			Triangles.Add(3 + (x * 20) + y * 4);

			Triangles.Add(1 + (x * 20) + y * 4);
			Triangles.Add(2 + (x * 20) + y * 4);
			Triangles.Add(3 + (x * 20) + y * 4);

			// 3. UVs
			UVs.Add(FVector2D(0.0f, 0.0f));
			UVs.Add(FVector2D(0.0f, 1.0f));
			UVs.Add(FVector2D(1.0f, 1.0f));
			UVs.Add(FVector2D(1.0f, 0.0f));
		}
	}

	if (ProceduralMeshPtr)
	{
		ProceduralMeshPtr->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexLinearColors, Tangents, true);
	}

	/*
	//Vertices.Add(FVector(0.0f, 0.0f, 0.0f));
	//Vertices.Add(FVector(100.0f, 0.0f, 0.0f));
	//Vertices.Add(FVector(0.0f, 100.0f, 0.0f));
	Vertices.Add(FVector(-100.0f, 0.0f, 100.0f));
	Vertices.Add(FVector(-100.0f, 0.0f, -100.0f));
	Vertices.Add(FVector(100.0f, 0.0f, 100.0f));
	Vertices.Add(FVector(100.0f, 0.0f, -100.0f));

	//Triangles.Add(0);
	//Triangles.Add(2);
	//Triangles.Add(1);

	// Triangle 1
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	// Triangle 2
	Triangles.Add(2);
	Triangles.Add(1);
	Triangles.Add(3);

	UVs.Add(FVector2D(0.0f, 0.0f));
	UVs.Add(FVector2D(0.0f, 1.0f));
	UVs.Add(FVector2D(1.0f, 0.0f));
	UVs.Add(FVector2D(1.0f, 1.0f));

	//Normals.Init(FVector(0.0f, 0.0f, 1.0f), 3);
	Normals.Init(FVector(0.0f, 0.0f, 0.0f), 3);

	VertexLinearColors.Init(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f), 3);

	//Tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), 3);
	Tangents.Init(FProcMeshTangent(0.0f, 0.0f, 0.0f), 3);

	if (ProceduralMeshPtr)
	{
*/
		/**
		*	Create/replace a section for this procedural mesh component.
		*	@param	SectionIndex		Index of the section to create or replace.
		*	@param	Vertices			Vertex buffer of all vertex positions to use for this mesh section.
		*	@param	Triangles			Index buffer indicating which vertices make up each triangle. Length must be a multiple of 3.
		*	@param	Normals				Optional array of normal vectors for each vertex. If supplied, must be same length as Vertices array.
		*	@param	UV0					Optional array of texture co-ordinates for each vertex. If supplied, must be same length as Vertices array.
		*	@param	VertexColors		Optional array of colors for each vertex. If supplied, must be same length as Vertices array.
		*	@param	Tangents			Optional array of tangent vector for each vertex. If supplied, must be same length as Vertices array.
		*	@param	bCreateCollision	Indicates whether collision should be created for this section. This adds significant cost.
		*/
/*
		// Don't use CreateMeshSection() function. It is deprecated. Use LinearColor version.
		//ProceduralMeshPtr->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);
		ProceduralMeshPtr->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexLinearColors, Tangents, true);
	}
*/
}

void ADMDMapChunk::TriangulateMesh()
{}
