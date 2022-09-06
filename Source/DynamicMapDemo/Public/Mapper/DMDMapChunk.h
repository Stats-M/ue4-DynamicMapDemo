// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"

// Header for base class Actor
#include "GameFramework/Actor.h"

// Headers for all components DMDMapChunk will consists of


#include "DMDMapChunk.generated.h"

/**
 * Class that defines a small chunk of map.
 * Full map consists from a set of chunks.
 */
UCLASS(BlueprintType, Blueprintable)
class DYNAMICMAPDEMO_API ADMDMapChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMDMapChunk();

protected:
	// Chunk width (preferrably even integer)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chunk Metrics")
	int32 ChunkSizeX = 10;

	// Chunk height (preferrably even integer)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chunk Metrics")
	int32 ChunkSizeY = 10;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
