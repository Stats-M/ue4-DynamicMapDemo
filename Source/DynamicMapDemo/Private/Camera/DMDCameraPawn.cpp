// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

#include "Camera/DMDCameraPawn.h"
#include "Components/InputComponent.h"  // for handling input
#include "EngineUtils.h"                // for iterators support

DEFINE_LOG_CATEGORY_STATIC(LogCamera, All, All)

// Sets default values
ADMDCameraPawn::ADMDCameraPawn()
{
	UE_LOG(LogCamera, Display, TEXT("ADMDCameraPawn constructor"));
	
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components.
	// CreateDefaultSubobject is preferred over AttachToComponent.
	// Argument - component name, used by UE (not displayed
	// name, although they are equal this time).
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	MaterialSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MaterialSphereMesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	// Adjust components scale for our convenience
	// NB. Each component scales itself + all childrens at once.
	// 1. Reduce sphere radius (it will scale springarm and camera as well)
	MaterialSphere->SetWorldScale3D(FVector(0.25f));
	// 2. Restore back half of Camera scale (0,25*2 = 0,5)
	Camera->SetWorldScale3D(FVector(2.0f));

	// Setting up hierarchy
	// 1. Setting the root component
	RootComponent = Scene;
	// 2. Setting subcomponents
	MaterialSphere->SetupAttachment(Scene);
	SpringArm->SetupAttachment(MaterialSphere);
	Camera->SetupAttachment(SpringArm);
}

// Called when the game mode starts or when spawned
void ADMDCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogCamera, Display, TEXT("ADMDCameraPawn::BeginPlay() - start"));

	// Try to set camera from the current pawn as active
	Camera->SetActive(true);

	// We will try to delete automatically spawned additional CameraActor (if exists)
	UE_LOG(LogCamera, Display, TEXT("Trying to get rid of auto-spawned camera actor (if any)..."));
	for (TActorIterator<ACameraActor> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		FString actor_name_ = (*ActorIt)->GetName();
		UE_LOG(LogCamera, Display, TEXT("Camera Actor founded: %s"), *actor_name_);

		// Check whether actor name is equal to auto-spawned "CameraActor_0"
		// i.e. if Compare("CameraActor_0") returns 0
//		if (!(*ActorIt)->GetName().Compare("CameraActor_0"))
		if (!actor_name_.Compare("CameraActor_0"))
		{
			// Auto-spawned camera founded. Try to delete it
			UE_LOG(LogCamera, Warning, TEXT("Default camera CameraActor_0 has been founded. Trying to delete..."));
			if ((*ActorIt)->Destroy())
			{
				UE_LOG(LogCamera, Display, TEXT("... deleted successfuly"));
			}
			else
			{
				UE_LOG(LogCamera, Error, TEXT("... unable to delete"));
			}
			break;  // no need to continue with loop, there was only 1 camera with such nameID
		}
	}

	UE_LOG(LogCamera, Display, TEXT("ADMDCameraPawn::BeginPlay() - exit"));
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

	UE_LOG(LogCamera, Display, TEXT("Binding input in ADMDCameraPawn"));

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

