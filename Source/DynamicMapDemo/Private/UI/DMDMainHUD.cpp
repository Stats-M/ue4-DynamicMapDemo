// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#include "UI/DMDMainHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ADMDMainHUD::DrawHUD()
{
    Super::DrawHUD();

}

void ADMDMainHUD::BeginPlay()
{
    Super::BeginPlay();

    // Local pointer to a HUD widget.
    // We can pass "this" or GetWorld() to it.
    UUserWidget* EditorHUDWidgetPtr = CreateWidget<UUserWidget>(GetWorld(), DMDEditorWidgetClass);
    if (EditorHUDWidgetPtr)
    {
        // zOrder = 0 by default, as we have only 1 widget here
        EditorHUDWidgetPtr->AddToViewport();
    }
}