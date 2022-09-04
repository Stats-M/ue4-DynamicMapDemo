// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev


#include "Mapper/DMDMapChunk.h"

// Sets default values
ADMDMapChunk::ADMDMapChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADMDMapChunk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADMDMapChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

