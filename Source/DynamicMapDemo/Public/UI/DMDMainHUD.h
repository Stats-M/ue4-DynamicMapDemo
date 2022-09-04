// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DMDMainHUD.generated.h"

/**
 * Main UI HUD class.
 * Other UI widgets get connected to this HUD
 */
UCLASS()
class DYNAMICMAPDEMO_API ADMDMainHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// Primary draw function for HUD
	virtual void DrawHUD() override;

protected:
	// Editor HUD Widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> DMDEditorWidgetClass;

	virtual void BeginPlay() override;
};
