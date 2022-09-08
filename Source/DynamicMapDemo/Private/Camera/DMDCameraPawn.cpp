// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#include "Camera/DMDCameraPawn.h"
#include "Components/InputComponent.h"  // for handling input

// Sets default values
ADMDCameraPawn::ADMDCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components.
	// CreateDefaultSubobject is preferred over AttachToComponent.
	// Argument - component name, used by UE (not displayed
	// name, although they are equal this time).
	ScenePtr = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	MaterialSpherePtr = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MaterialSphereMesh"));
	SpringArmPtr = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraPtr = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FloatingPawnMovementPtr = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	// Adjust components scale for our convenience
	// NB. Each component scales itself + all childrens at once.
	// 1. Reduce sphere radius (it will scale springarm and camera as well)
	MaterialSpherePtr->SetWorldScale3D(FVector(0.25f));
	// 2. Restore back half of Camera scale (0,25*2 = 0,5)
	CameraPtr->SetWorldScale3D(FVector(2.0f));

	// Setting up hierarchy
	// 1. Setting the root component
	RootComponent = ScenePtr;
	// 2. Setting subcomponents
	MaterialSpherePtr->SetupAttachment(ScenePtr);
	SpringArmPtr->SetupAttachment(MaterialSpherePtr);
	CameraPtr->SetupAttachment(SpringArmPtr);

	//UE_LOG(LogTemp, Error, TEXT("%s"), *tmpStr);
}

// Called when the game starts or when spawned
void ADMDCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADMDCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADMDCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Handle axis mapping (continuous input) for our camera

	//BindAxis args are: Mapping name (from UE), Object who will handle, handler function name
	PlayerInputComponent->BindAxis("CameraMoveForward", this, &ADMDCameraPawn::MoveForward);
	PlayerInputComponent->BindAxis("CameraMoveRight", this, &ADMDCameraPawn::MoveRight);
}

void ADMDCameraPawn::MoveForward(float Amount)
{
	//AddMovementInput args are: movement direction, scale
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ADMDCameraPawn::MoveRight(float Amount)
{
	//AddMovementInput args are: movement direction, scale
	AddMovementInput(GetActorRightVector(), Amount);
}

