// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#include "Mapper/DMDHexGrid.h"

DEFINE_LOG_CATEGORY_STATIC(LogHexGrid, All, All)

// Sets default values
ADMDHexGrid::ADMDHexGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject is preferred over AttachToComponent.
	// Argument - component name that will be used by UE
	// (it is not the same as displayed name of parent class).
	ScenePtr = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	// Setting up hierarchy
	// 1. Setting the root component for AActor
	RootComponent = ScenePtr;
	//ScenePtr->bUseAttachParentBound = true;  // Use parent actor bounds instead of its own (optimization)
	// 2. Setting subcomponents
	// none yet
}

// Called when the game mode starts or when spawned
void ADMDHexGrid::BeginPlay()
{
	Super::BeginPlay();

	// Init map variables we will work with
	InitGridVariables();

#if (!UE_BUILD_SHIPPING)
	UE_LOG(LogHexGrid, Display, TEXT("ADMDMapChunk::BeginPlay() - init cell labels creation"));

	// This section creates independent actors, not subobjects.
	// That's why their spawn placed here and not in ADMDHexGrid() Ctor

	CoordTextActors.Reserve(cellsCountTotal);                // Reserve memory. 1 text actor per 1 cell
	CoordTextActors.SetNumZeroed(cellsCountTotal, false);    // Zero-init reserved memory, no shrink
	UE_LOG(LogHexGrid, Display, TEXT("Label pointers array has %i elements, memory reserved"), CoordTextActors.Num());

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		UE_LOG(LogHexGrid, Display, TEXT("UWorld* pointer acquired sucessfully"));

		int i = 0;  // Linear counter for 1-dimensional objects array
		// Traverse all grid cells (square array)
		for (int grid_x = 0; grid_x < cellsCountX; ++grid_x)
		{
			for (int grid_y = 0; grid_y < cellsCountY; ++grid_y)
			{
				// 1. Spawn actor

				FActorSpawnParameters spawn_params_;
				spawn_params_.OverrideLevel = GetOwner()->GetLevel();
				FString actor_name_ = FString::Printf(TEXT("CellCoordsActor-%04d-%04d"),
													  grid_x, 
													  grid_y);
				UE_LOG(LogHexGrid, Display, TEXT("Generated actor nameID: %s"), *actor_name_);
				spawn_params_.Name = FName(actor_name_);

				// Location is a sum of current cell location and label origin
				FVector Location = FVector(grid_x * UDMDHexMetrics::OuterRadius, 
										   grid_y * UDMDHexMetrics::OuterRadius,
										   0.0f) 
					             + LabelsStartLocation;
				FRotator Rotation = FRotator(90.0f, 180.0f, 0.0f);        // Text "lays" in XY plane
				CoordTextActors[i] = World->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), Location, Rotation, spawn_params_);

				// 2. Set up Actor's text
				if (CoordTextActors[i])
				{
					UE_LOG(LogHexGrid, Display, TEXT("Actor with label= %s and nameID= %s created"),
						   *CoordTextActors[i]->GetActorLabel(),
						   *CoordTextActors[i]->GetFName().ToString());

					UTextRenderComponent* const TextRenderComponentPtr = CoordTextActors[i]->GetTextRender();
					if (TextRenderComponentPtr)
					{
						FString actor_text_ = FString::Printf(TEXT("%i-%i"),
															  grid_x,
															  grid_y);
						TextRenderComponentPtr->SetText(actor_text_);
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

				++i;  // This item has been created, advance to the next one
			}
		}

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
			FVector Location = ScenePtr->GetComponentLocation();
			//FRotator Rotation = FRotator(0.0f, 90.0f, 180.0f);
			FRotator Rotation = FRotator(90.0f, 180.0f, 0.0f);        // Text "lays" in XY plane
			//FRotator Rotation = ScenePtr->GetComponentRotation();
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

#endif
}

// Called every frame
void ADMDHexGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADMDHexGrid::InitGridVariables()
{
	// Enforce limits for map variables before spawning actors
	if (ChunksAmountX > UDMDHexMetrics::ChunksAmountXMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks amount (width) %i exceeds the limit. Fixed."), ChunksAmountX);
		ChunksAmountX = UDMDHexMetrics::ChunksAmountXMax;
	}

	if (ChunksAmountY > UDMDHexMetrics::ChunksAmountYMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks amount (height) %i exceeds the limit. Fixed."), ChunksAmountY);
		ChunksAmountY = UDMDHexMetrics::ChunksAmountYMax;
	}

	if (ChunkSizeX > UDMDHexMetrics::ChunkSizeXMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks size (width) %i exceeds the limit. Fixed."), ChunkSizeX);
		ChunkSizeX = UDMDHexMetrics::ChunkSizeXMax;
	}

	if (ChunkSizeY > UDMDHexMetrics::ChunkSizeYMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks size (height) %i exceeds the limit. Fixed."), ChunkSizeY);
		ChunkSizeY = UDMDHexMetrics::ChunkSizeYMax;
	}

	// Init misc map variables
	cellsCountX = ChunksAmountX * ChunkSizeX;
	cellsCountY = ChunksAmountY * ChunkSizeY;
	cellsCountTotal = cellsCountX * cellsCountY;
	chunksCountTotal = ChunksAmountX * ChunksAmountY;
}
