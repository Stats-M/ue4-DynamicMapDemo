// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DMDStaticHelpersLibrary.generated.h"

/**
 * Static library of helper functions.
 * Enables to create our own version of UE4 C++ without having 
 * to modify the engine code and recompile it constantly.
 * 
 * A static library can have FORCEINLINE functions (resides in .h 
 * file only) as well as regular .cpp functions
 */
UCLASS()
class DYNAMICMAPDEMO_API UDMDStaticHelpersLibrary : public UObject
{
	GENERATED_BODY()

public:

	UDMDStaticHelpersLibrary();

	// Checks whether TheActor is valid
	// FORCEINLINE function
	static FORCEINLINE bool IsValid(AActor* TheActor)
	{
		if (!TheActor)
		{
			return false;
		}
		if (!TheActor->IsValidLowLevel())
		{
			return false;
		}
		return true;
	}

	//Regular cpp function stub. Edit freely.
	static int32 ComplicatedFunctionStub();
};
