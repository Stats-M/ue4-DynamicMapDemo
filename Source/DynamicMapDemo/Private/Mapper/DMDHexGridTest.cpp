// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

// Headers required to run tests
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"           // for simple tests
#include "Tests/AutomationEditorCommon.h"  // for tests that required simulation (a level to spawn actors in)

#include "Mapper/DMDHexGrid.h"             // Test subject

//#include "GameFramework/PlayerInput.h"     // In case if user input required for tests
#include "DMDGameModeBase.h"

#if WITH_DEV_AUTOMATION_TESTS

// EditorContext defines that we want to be able to run this test in the Editor
// ProductFilter is for defining how long the test will take to run
// For more information check AutomationTest.h
// Test name follows the pattern: Unit.ClassToTest.TestName
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHexGridInitValuesTest, "Mapper.HexGrid.InitValues", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

// Each test function must be named RunTest
// The struct name here "FHexGridInitValuesTest" must match the one in the macro above
bool FHexGridInitValuesTest::RunTest(const FString& Parameters)
{

	// Create a new level in order not to interfere with actors and 
	// cause them to get deleted after test ends
	UWorld* TestWorld = FAutomationEditorCommonUtils::CreateNewMap();

	if (TestWorld)
	{
		ADMDHexGrid* Grid = TestWorld->SpawnActor<ADMDHexGrid>();

		if (Grid)
		{
			Grid->DummyInitVariables();
			if (Grid->GetCellsCountX() == 0)
			{
				// If we call AddError, the test will automatically fail
				AddError(TEXT("Cells count along X axis is 0. Must be positive."));
			}
			if (Grid->GetCellsCountY() == 0)
			{
				// If we call AddError, the test will automatically fail
				AddError(TEXT("Cells count along Y axis is 0. Must be positive."));
			}
			/*
			if (Grid->cellsCountTotal == 0)
			{
				// If we call AddError, the test will automatically fail
				AddError(TEXT("Total cells count is 0. Must be positive."));
			}
			if (Grid->chunksCountTotal == 0)
			{
				// If we call AddError, the test will automatically fail
				AddError(TEXT("Total chunks count is 0. Must be positive."));
			}
			*/

			Grid->Destroy();
		}
		else
		{
			AddError(TEXT("Unable to run test: Grid == nullptr"));
		}
	}
	else
	{
		AddError(TEXT("Unable to run test: TestWorld == nullptr"));
	}

	// We can return "false" to fail the error, but  
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS