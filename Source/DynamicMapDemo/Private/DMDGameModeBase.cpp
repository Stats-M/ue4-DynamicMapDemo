// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev


#include "DMDGameModeBase.h"
#include "Camera/DMDCameraPawn.h"          // adds our camera controller to GameMode
#include "Camera/DMDPlayerController.h"    // adds our player input controller to GameMode
#include "UI/DMDMainHUD.h"                 // adds primary HUD to GameMode

ADMDGameModeBase::ADMDGameModeBase()
{
    // Set default classes (see World Properties)
    DefaultPawnClass = ADMDCameraPawn::StaticClass();                // set camera class for World settings \ GameMode
    PlayerControllerClass = ADMDPlayerController::StaticClass();     // set controller class for World settings \ GameMode
    HUDClass = ADMDMainHUD::StaticClass();                           // set HUD class for World settings \ GameMode
}