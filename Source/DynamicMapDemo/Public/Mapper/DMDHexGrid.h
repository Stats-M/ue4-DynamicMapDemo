// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMDHexGrid.generated.h"

/**
 * Class defines a hexagonal map, consisted from a set 
 * of small map chunks.
 */
UCLASS()
class DYNAMICMAPDEMO_API ADMDHexGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMDHexGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
