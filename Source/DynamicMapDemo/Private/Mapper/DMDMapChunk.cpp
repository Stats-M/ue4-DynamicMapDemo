// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#include "Mapper/DMDMapChunk.h"

DEFINE_LOG_CATEGORY_STATIC(LogHexGrid, All, All)

// Sets default values
ADMDMapChunk::ADMDMapChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject is preferred over AttachToComponent.
	// Argument - component name that will be used by UE
	// (it is not the same as displayed name of parent class).
	ScenePtr = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	ProceduralMeshPtr = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshChunk"));

	// Setting up hierarchy
	// 1. Setting the root component for AActor
	RootComponent = ScenePtr;
	ScenePtr->bUseAttachParentBound = true;  // Use parent actor bounds instead of its own (optimization)
	// 2. Setting subcomponents
	ProceduralMeshPtr->SetupAttachment(ScenePtr);
}

// Called when the game mode starts or when spawned
void ADMDMapChunk::BeginPlay()
{
	Super::BeginPlay();
	
	ClearMeshData();

	CreateMesh();
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

		// Don't use CreateMeshSection() function. It is deprecated. Use LinearColor version.
		//ProceduralMeshPtr->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);
		ProceduralMeshPtr->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexLinearColors, Tangents, true);
	}
}

void ADMDMapChunk::TriangulateMesh()
{}
