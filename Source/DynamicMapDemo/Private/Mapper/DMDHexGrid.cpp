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

	// Enforce limits for map variables before spawning actors
	if (ChunksAmountX > UDMDHexMetrics::ChunksAmountXMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks amount (width) exceeds the limit. Fixed."));
		ChunksAmountX = UDMDHexMetrics::ChunksAmountXMax;
	}

	if (ChunksAmountY > UDMDHexMetrics::ChunksAmountYMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks amount (height) exceeds the limit. Fixed."));
		ChunksAmountY = UDMDHexMetrics::ChunksAmountYMax;
	}

	if (ChunkSizeX > UDMDHexMetrics::ChunkSizeXMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks size (width) exceeds the limit. Fixed."));
		ChunkSizeX = UDMDHexMetrics::ChunkSizeXMax;
	}

	if (ChunkSizeY > UDMDHexMetrics::ChunkSizeYMax)
	{
		UE_LOG(LogHexGrid, Warning, TEXT("Chunks size (height) exceeds the limit. Fixed."));
		ChunkSizeY = UDMDHexMetrics::ChunkSizeYMax;
	}

#if (!UE_BUILD_SHIPPING)
	UE_LOG(LogHexGrid, Display, TEXT("ADMDMapChunk::BeginPlay() - init cell labels creation"));

	// This section creates independent actors, not subobjects.
	// That's why their spawn placed here and not in ADMDMapChunk() Ctor

	int32 array_size_ = ChunksAmountX * ChunksAmountY;
	CoordTextActors.Reserve(array_size_);                // Reserve memory
	CoordTextActors.SetNumZeroed(array_size_, false);    // Zero-init reserved memory, no shrink
	UE_LOG(LogHexGrid, Display, TEXT("Label pointers array has %i elements allocated"), CoordTextActors.Num());

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		UE_LOG(LogHexGrid, Display, TEXT("UWorld* pointer acquired sucessfully"));

		//int i = 0;
		for (int i = 0; i < array_size_; ++i)
		{
			// Set new actor properties
			FActorSpawnParameters spawn_params_;
			//spawn_params_.bDeferConstruction = true; // We defer construction so that we set ParentComponentActor prior to component registration so they appear selected
			//spawn_params_.bAllowDuringConstructionScript = true;
			//spawn_params_.OverrideLevel = GetOwner()->GetLevel();
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
	}
	else
	{
		UE_LOG(LogHexGrid, Error, TEXT("Unable to acquire UWorld* pointer"));
	}

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

#endif
}

// Called every frame
void ADMDHexGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

