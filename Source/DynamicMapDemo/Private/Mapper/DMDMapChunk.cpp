// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev


#include "Mapper/DMDMapChunk.h"

// Sets default values
ADMDMapChunk::ADMDMapChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create component
	// CreateDefaultSubobject is preferred over AttachToComponent.
	// Argument - component name, used by UE (not displayed
	// name, although they are equal this time).
	ProceduralMeshPtr = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshChunk"));

	// Setting up hierarchy
	// 1. Setting the root component for AActor
	//RootComponent = ProceduralMeshPtr;
	// 2. Setting subcomponents
	//   (none while there is no other components yet)
}

// Called when the game starts or when spawned
void ADMDMapChunk::BeginPlay()
{
	Super::BeginPlay();
	
	ClearMeshData();

	Vertices.Add(FVector(0.0f, 0.0f, 0.0f));
	Vertices.Add(FVector(100.0f, 0.0f, 0.0f));
	Vertices.Add(FVector(0.0f, 100.0f, 0.0f));

	Triangles.Add(0);
	Triangles.Add(2);
	Triangles.Add(1);

	UVs.Add(FVector2D(0.0f, 0.0f));
	UVs.Add(FVector2D(1.0f, 0.0f));
	UVs.Add(FVector2D(0.0f, 1.0f));

	//uvs.Init(FVector2D(0.0f, 0.0f), 3);
	Normals.Init(FVector(0.0f, 0.0f, 1.0f), 3);
	VertexColors.Init(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f), 3);
	Tangents.Init(FProcMeshTangent(1.0f, 0.0f, 0.0f), 3);

	//Function that creates mesh section
	ProceduralMeshPtr->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, VertexColors, Tangents, false);
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
	VertexColors.Empty();
	Tangents.Empty();
}

