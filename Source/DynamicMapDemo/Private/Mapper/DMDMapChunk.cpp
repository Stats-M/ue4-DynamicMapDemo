// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#include "Mapper/DMDMapChunk.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

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

	/*
	if (TextRenderActorPtr)
	{
		UTextRenderComponent* const TextRenderComponentPtr = TextRenderActorPtr->GetTextRender();
		if (TextRenderComponentPtr)
		{
			TextRenderComponentPtr->SetText(FText::FromString("YOUR TEXT AS FText HERE"));
			//TextRenderComponentPtr->SetText(FText("YOUR TEXT AS FText HERE"));
		}
		else
		{
			// Failure handling (TextRenderComponentPtr is nullptr)
		}
	}
	else
	{
		// Failure handling (TextRenderActorPtr is nullptr)
	}
	*/

	/* Old constructor with usage of Scene component
	ScenePtr = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	ProceduralMeshPtr = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshChunk"));

	// Setting up hierarchy
	// 1. Setting the root component for AActor
	RootComponent = ScenePtr;
	RootComponent = ProceduralMeshPtr;
	// 2. Setting subcomponents
	ProceduralMeshPtr->SetupAttachment(ScenePtr);
	*/
}

// Called when the game mode starts or when spawned
void ADMDMapChunk::BeginPlay()
{
	Super::BeginPlay();
	
	ClearMeshData();

	CreateMesh();

	UE_LOG(LogBaseGeometry, Warning, TEXT("HERE"));

// This section creates independent actors, not subobjects.
// That's why their spawn placed here and not in ADMDMapChunk() Ctor
//#if WITH_EDITOR  // Use more strict UE_BUILD_SHIPPING to check if Config==Shipping
	CoordTextActors.Reserve(ChunkSizeX * ChunkSizeY);                // Reserve memory
	CoordTextActors.SetNumZeroed(ChunkSizeX * ChunkSizeY, false);    // Zero-init reserved memory, no shrink

	UE_LOG(LogBaseGeometry, Warning, TEXT("Array size: %i"), CoordTextActors.Num());

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		UE_LOG(LogBaseGeometry, Warning, TEXT("Got UWorld*"));

		//int i = 0;
		for (int i = 0; i < ChunkSizeX * ChunkSizeY; ++i)
		{
			// Set new actor properties
			FActorSpawnParameters Params;
			//			Params.bDeferConstruction = true; // We defer construction so that we set ParentComponentActor prior to component registration so they appear selected
						//Params.bAllowDuringConstructionScript = true;
						//Params.OverrideLevel = GetOwner()->GetLevel();
			FString tmp_name = "TextRenderActor" + FString::FromInt(i);
			UE_LOG(LogBaseGeometry, Warning, TEXT("Got actor name: %s"), *tmp_name);
			Params.Name = FName(tmp_name);

			// Set actor location to be the same as Scene component
			FVector Location = ScenePtr->GetComponentLocation();
			//FRotator Rotation = FRotator(0.0f, 90.0f, 180.0f);
			FRotator Rotation = FRotator(90.0f, 180.0f, 0.0f);        // Text "lays" in XY plane
			//FRotator Rotation = ScenePtr->GetComponentRotation();
			// Spawn actor of desired class
			CoordTextActors[i] = World->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), Location, Rotation, Params);

			//CoordTextActors[i]->GetTextRender()->SetText(FText::FromString(TEXT("Dynamic Text")));
			//CoordTextActors[i]->GetTextRender()->SetTextRenderColor(FColor::Red);
			//CoordTextActors[i]->SetActorScale3D(FVector(5.f, 5.f, 5.f));
			if (CoordTextActors[i])
			{
				UE_LOG(LogBaseGeometry, Warning, TEXT("Actor created"));
			}
			else
			{
				UE_LOG(LogBaseGeometry, Error, TEXT("Creation failed"));
			}
		}
	}
//#endif
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

		// Don't use this function. It is deprecated. Use LinearColor version.
		//ProceduralMeshPtr->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, true);
		ProceduralMeshPtr->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexLinearColors, Tangents, true);
	}
}

void ADMDMapChunk::TriangulateMesh()
{}
