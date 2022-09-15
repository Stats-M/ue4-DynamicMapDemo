// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DMDHexCell.generated.h"

/**
 * Class defines 1 single cell of a hexagonal map.
 * This class does't have any visual representation, 
 * all visuals (rendering) handled by UDMDMapChunk
 */
UCLASS()
class DYNAMICMAPDEMO_API UDMDHexCell : public UObject
{
	GENERATED_BODY()
	
};
