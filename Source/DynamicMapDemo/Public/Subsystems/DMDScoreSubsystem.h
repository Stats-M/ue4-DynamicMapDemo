// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DMDScoreSubsystem.generated.h"

/**
 * Score subsystem.
 * Handles all score-related information.
 * Based on GameInstance subsystem (persistent through all app execution).
 */
UCLASS(DisplayName = "ScoreSubsystem")
class DYNAMICMAPDEMO_API UDMDScoreSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	/* CLASS METHODS EXAMPLE:

	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	UFUNCTION(BlueprintCallable, Category = ScoreSubsystem)
	void IncrementMultiplier(int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = ScoreSubsystem)
	int32 GetMultiplier();

	UFUNCTION(BlueprintCallable, Category = ScoreSubsystem)
	void AddScore(int32 BaseScore);

	UFUNCTION(BlueprintCallable, Category = ScoreSubsystem)
	int32 GetTotalScore(int32 BaseScore);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreAdded, int32, UnmultipledAddedScore);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChanged, int32, TotalNewScore);

	UPROPERTY(BlueprintAssignable, Category = ScoreSubsystem)
	FScoreAdded OnScoreAdded;

	UPROPERTY(BlueprintAssignable, Category = ScoreSubsystem)
	FScoreChanged OnScoreChanged;
	*/
};
