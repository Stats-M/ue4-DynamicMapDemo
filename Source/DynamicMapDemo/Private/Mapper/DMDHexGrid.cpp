// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#include "Mapper/DMDHexGrid.h"

DEFINE_LOG_CATEGORY_STATIC(LogHexGrid, All, All)

// Sets default values
ADMDHexGrid::ADMDHexGrid()
{
	UE_LOG(LogHexGrid, Display, TEXT("ADMDHexGrid constructor"));
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject is preferred over AttachToComponent.
	// Argument - component name that will be used by UE
	// (it is not the same as displayed name of parent class).
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	// HexGrid is a static actor. Camera flies over it.
	Scene->Mobility = EComponentMobility::Static;

	// Setting up hierarchy
	// 1. Setting the root component for AActor
	RootComponent = Scene;
	//Scene->bUseAttachParentBound = true;  // Use parent actor bounds instead of its own (optimization)
	// 2. Setting subcomponents
	// none yet
}

// Creates a cell instance and adds it to cell array(s)
//  X,Y - cell indexes in rectangular grid
//  Index - cell index in linear cells array
void ADMDHexGrid::CreateCell(int32 X, int32 Y, int32 Index)
{
	// Calculate cell's global world coordinates from its indexes
	FVector Position;
	Position.X = X * UDMDHexMetrics::OuterRadius;
	Position.Y = Y * UDMDHexMetrics::InnerRadius;
	Position.Z = 0.0f;

	GridCells[Index] = NewObject<UDMDHexCell>(UDMDHexCell::StaticClass());

	// Apply global coordinates shift (grid start origin) here.
	// Proc: we do not require to do any calculations later
	// Cons: we loose ability to change grid origin on the fly.
	GridCells[Index]->Location = Position + GridStartLocation;

}

// Called when the game mode starts or when spawned
void ADMDHexGrid::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogHexGrid, Display, TEXT("ADMDHexGrid::BeginPlay() - start"));

	// Init map variables we will work with
	InitGridVariables();

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		UE_LOG(LogHexGrid, Display, TEXT("UWorld* pointer acquired sucessfully"));

		int i = 0;  // Linear counter for 1-dimensional arrays (declared outside #if)

		// STEP 1. SPAWN TextRender ACTORS
#if (!UE_BUILD_SHIPPING)
		UE_LOG(LogHexGrid, Display, TEXT("Init cell labels creation"));

		// This section creates independent actors, not subobjects.
		// That's why their spawn placed here and not in ADMDHexGrid() Ctor

		CoordTextActors.Reserve(cellsCountTotal);                // Reserve memory. 1 text actor per 1 cell
		CoordTextActors.SetNumZeroed(cellsCountTotal, false);    // Zero-init reserved memory, no shrink
		UE_LOG(LogHexGrid, Display, TEXT("Label pointers array has %i elements, memory reserved"), CoordTextActors.Num());

		i = 0;  // Reset counter
		// Traverse all cells (square array)
		// NB: grid_x and grid_y are referred to Cartesian [X,Y] axis, not UE [Forward,Right] axis
		for (int32 grid_y = 0; grid_y < cellsTotalCountHeight; ++grid_y)
		{
			for (int32 grid_x = 0; grid_x < cellsTotalCountWidth; ++grid_x)
			{
				// Spawn Label actor
				FActorSpawnParameters spawn_params_;
				spawn_params_.OverrideLevel = World->GetCurrentLevel();
				FString actor_name_ = FString::Printf(TEXT("CellCoordsActor-%04d-%04d"),
													  grid_x, 
													  grid_y);
				UE_LOG(LogHexGrid, Display, TEXT("Generated actor nameID: %s"), *actor_name_);
				spawn_params_.Name = FName(actor_name_);

				// Location is a sum of labels origin and current cell location offset
				FVector Location = LabelsStartLocation + FVector(grid_y * UDMDHexMetrics::OuterRadius * 2 + UDMDHexMetrics::OuterRadius,
																 grid_x * UDMDHexMetrics::InnerRadius * 2 + UDMDHexMetrics::InnerRadius,
																 0.0f);
				FRotator Rotation = FRotator(90.0f, 180.0f, 0.0f);        // Text "lays" in XY plane
				CoordTextActors[i] = World->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), Location, Rotation, spawn_params_);
				UE_LOG(LogHexGrid, Display, TEXT("Text label Actor spawned at coordinates %s"), *Location.ToString());

				// Set up actor's text
				if (CoordTextActors[i])
				{
					UE_LOG(LogHexGrid, Display, TEXT("Actor with label= %s and nameID= %s created"),
						   *CoordTextActors[i]->GetActorLabel(),
						   *CoordTextActors[i]->GetFName().ToString());

					UTextRenderComponent* const TextRenderComponentPtr = CoordTextActors[i]->GetTextRender();
					if (TextRenderComponentPtr)
					{
						FString actor_text_ = FString::Printf(TEXT("%i<br>%i"),
															  grid_x,
															  grid_y);
						TextRenderComponentPtr->SetWorldSize(LabelFontSize);    // Set font size
						// SetText(FString) is deprecated. Use SetText(FText)
						TextRenderComponentPtr->SetText(FText::FromString(actor_text_));
					}
					else
					{
						UE_LOG(LogHexGrid, Error, TEXT("Unable to set cell label, TextRenderComponent is nullptr (x = %i, y = %i)"),
							   grid_x,
							   grid_y);
					}

				}
				else
				{
					UE_LOG(LogHexGrid, Error, TEXT("Creation of actor with label= %s and nameID= %s failed"),
						   *CoordTextActors[i]->GetActorLabel(),
						   *CoordTextActors[i]->GetFName().ToString());
				}

				++i;  // Advance linear counter to the next element
			}
		}
#endif

		// STEP 2. SPAWN MapChunk ACTORS
		UE_LOG(LogHexGrid, Display, TEXT("Init map chunks creation"));

		MapChunks.Reserve(chunksCountTotal);                // Reserve memory.
		MapChunks.SetNumZeroed(chunksCountTotal, false);    // Zero-init reserved memory, no shrink
		UE_LOG(LogHexGrid, Display, TEXT("Map chunks array has %i elements, memory reserved"), MapChunks.Num());

		i = 0;  // Reset counter
		// Traverse all chunks.
		// NB: chunk_x and chunk_y are referred to Cartesian [X,Y] axis, not UE [Forward,Right] axis
		for (int32 chunk_y = 0; chunk_y < TotalChunksCountHeight; ++chunk_y)
		{
			for (int32 chunk_x = 0; chunk_x < TotalChunksCountWidth; ++chunk_x)
			{
				// Spawn actor
				FActorSpawnParameters spawn_params_;
				spawn_params_.OverrideLevel = World->GetCurrentLevel();
				FString actor_name_ = FString::Printf(TEXT("MapChunkActor-%04d-%04d"),
													  chunk_x,
													  chunk_y);
				UE_LOG(LogHexGrid, Display, TEXT("Generated actor nameID: %s"), *actor_name_);
				spawn_params_.Name = FName(actor_name_);

				// Location is a sum of grid origin and chunk location offset
				FVector Location = GridStartLocation + FVector(chunk_y * UDMDHexMetrics::OuterRadius * 1.75f * ChunkSizeHeight,
															   chunk_x * UDMDHexMetrics::InnerRadius * 2.0f * ChunkSizeWidth,
															   0.0f);
				FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
				MapChunks[i] = World->SpawnActor<ADMDMapChunk>(ADMDMapChunk::StaticClass(), Location, Rotation, spawn_params_);
				
				// Try to optimize performance by ignoring overlapping events for the mesh
				MapChunks[i]->bGenerateOverlapEventsDuringLevelStreaming = false;

				++i;  // Advance linear counter to the next element
			}
		}

		// STEP 3. Reserve memory for grid cells
		UE_LOG(LogHexGrid, Display, TEXT("Reserve memory for grid cells"));

		GridCells.Reserve(cellsCountTotal);                // Reserve memory.
		GridCells.SetNumZeroed(cellsCountTotal, false);    // Zero-init reserved memory, no shrink
		UE_LOG(LogHexGrid, Display, TEXT("Grid cells array has %i elements, memory reserved"), GridCells.Num());

		/* OLD TEST CODE
		for (int i = 0; i < cellsCountTotal; ++i)
		{
			// Set new actor properties
			FActorSpawnParameters spawn_params_;
			//spawn_params_.bDeferConstruction = true; // We defer construction so that we set ParentComponentActor prior to component registration so they appear selected
			//spawn_params_.bAllowDuringConstructionScript = true;
			spawn_params_.OverrideLevel = GetOwner()->GetLevel();
			FString actor_name_prefix_ = "CellCoordsActor" + FString::FromInt(i);
			FString actor_name_ = FString::Printf(TEXT("CellCoordsActor%04d"), i);
			UE_LOG(LogHexGrid, Display, TEXT("Generated actor nameID: %s"), *actor_name_prefix_);
			spawn_params_.Name = FName(actor_name_prefix_);

			// Set actor location to be the same as Scene component
			FVector Location = Scene->GetComponentLocation();
			//FRotator Rotation = FRotator(0.0f, 90.0f, 180.0f);
			FRotator Rotation = FRotator(90.0f, 180.0f, 0.0f);        // Text "lays" in XY plane
			//FRotator Rotation = Scene->GetComponentRotation();
			// Spawn actor of desired class
			CoordTextActors[i] = World->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), Location, Rotation, spawn_params_);

			//CoordTextActors[i]->GetTextRender()->SetText(FText::FromString(TEXT("Dynamic Text")));
			//CoordTextActors[i]->GetTextRender()->SetTextRenderColor(FColor::Red);
			//CoordTextActors[i]->SetActorScale3D(FVector(5.f, 5.f, 5.f));

			if (CoordTextActors[i])
			{
				UE_LOG(LogHexGrid, Display, TEXT("Actor with label= %s and nameID= %s created"),
					   *CoordTextActors[i]->GetActorLabel(),
					   *CoordTextActors[i]->GetFName().ToString());
			}
			else
			{
				UE_LOG(LogHexGrid, Error, TEXT("Creation of actor with label= %s and nameID= %s failed"),
					   *CoordTextActors[i]->GetActorLabel(),
					   *CoordTextActors[i]->GetFName().ToString());
			}
		}
		*/
	}
	else
	{
		UE_LOG(LogHexGrid, Error, TEXT("Unable to acquire UWorld* pointer"));
	}

	/*
	CoordTextActors[2]->SetActorLocation(FVector(0.0f, 0.0f, -50.0f));
	UTextRenderComponent* const TextRenderComponentPtr = CoordTextActors[2]->GetTextRender();
	if (TextRenderComponentPtr)
	{
		TextRenderComponentPtr->SetText(FText::FromString("YOUR TEXT AS FText HERE"));
		//TextRenderComponentPtr->SetText(TEXT("YOUR TEXT AS FText HERE"));
	}
	else
	{
		// Failure handling (TextRenderComponentPtr is nullptr)
	}
	*/

	UE_LOG(LogHexGrid, Display, TEXT("ADMDHexGrid::BeginPlay() - exit"));

}

// Called every frame
void ADMDHexGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADMDHexGrid::InitGridVariables()
{
	// Enforce limits for map variables before spawning actors
	if (TotalChunksCountWidth > UDMDHexMetrics::TotalChunksCountWidthMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks amount (width) %i exceeds the limit. Fixed."), TotalChunksCountWidth);
		TotalChunksCountWidth = UDMDHexMetrics::TotalChunksCountWidthMax;
	}

	if (TotalChunksCountHeight > UDMDHexMetrics::TotalChunksCountHeightMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks amount (height) %i exceeds the limit. Fixed."), TotalChunksCountHeight);
		TotalChunksCountHeight = UDMDHexMetrics::TotalChunksCountHeightMax;
	}

	if (ChunkSizeHeight > UDMDHexMetrics::ChunkSizeHeightMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks size (height) %i exceeds the limit. Fixed."), ChunkSizeHeight);
		ChunkSizeHeight = UDMDHexMetrics::ChunkSizeHeightMax;
	}

	if (ChunkSizeWidth > UDMDHexMetrics::ChunkSizeWidthMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunk size (width) %i exceeds the limit. Fixed."), ChunkSizeWidth);
		ChunkSizeWidth = UDMDHexMetrics::ChunkSizeWidthMax;
	}

	// Init misc map variables
	cellsTotalCountHeight = TotalChunksCountHeight * ChunkSizeHeight;
	cellsTotalCountWidth = TotalChunksCountWidth * ChunkSizeWidth;
	cellsCountTotal = cellsTotalCountWidth * cellsTotalCountHeight;
	chunksCountTotal = TotalChunksCountWidth * TotalChunksCountHeight;

	// Adjust cell labels location to start somewhere
	// near cell center: half cell radius up (X axis)
	// and quater cell radius left (Y axis)
	// Upd: adjustment now adds directly in Label actor spawn
	//LabelsStartLocation.X += UDMDHexMetrics::OuterRadius * 0.5f;
	//LabelsStartLocation.Y -= UDMDHexMetrics::OuterRadius * 0.25f;
}
