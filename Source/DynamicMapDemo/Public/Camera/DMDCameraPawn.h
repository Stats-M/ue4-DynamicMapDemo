// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev
//
// This is a parent C++ class for freely movable strategic camera.
// It consists of Scene-StaticMesh-SpringArm-Camera and FloatingPawnMovement.
// Details:
// -All components being created programmatically and accessed via BP.
// -Rotation controlled by Sphere component in BP, initial value = -70 degrees Y.
// -Mesh, material and other asset-related properties are set via BP.
// -All BP scripts have either their stubs in C++ (BlueprintImplementableEvent)
// or some default logic in C++ and override in BP (BlueprintNativeEvent).

#pragma once

#include "CoreMinimal.h"

// Header for base class Pawn
#include "GameFramework/Pawn.h"

// Headers for all components, our child BP_DMDCameraPawn will consists of
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "DMDCameraPawn.generated.h"

/**
 *
 */
UCLASS()
class DYNAMICMAPDEMO_API ADMDCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADMDCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Scene component (root for CameraPawn)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* ScenePtr;  //Scene component (root for CameraPawn)

	// StaticMesh (material sphere) component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MaterialSpherePtr;  //StaticMesh (material sphere) component

	// SpringArm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmPtr;  //SpringArm component

	// Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraPtr;  //Camera component

	// FloatingPawnMovement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFloatingPawnMovement* FloatingPawnMovementPtr;  //FloatingPawnMovement component

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
};
