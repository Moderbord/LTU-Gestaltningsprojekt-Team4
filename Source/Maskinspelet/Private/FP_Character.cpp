// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FP_Character.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "InteractableInterface.h"
#include "PhysicsEngine/PhysicsHandleComponent.h" 
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);


// Sets default values
AFP_Character::AFP_Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	//Set up the physics handel for pickup and inspect
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	// Create VR Controllers.
	//R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	//R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	//R_MotionController->SetupAttachment(RootComponent);
	//L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	//L_MotionController->SetupAttachment(RootComponent);

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;
}

// Called when the game starts or when spawned
void AFP_Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}


void AFP_Character::OnFire()
{
	//Hitscan variables
	bool bHit = LineTrace();
	//Hitscan
	if (bHit)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, GetDebugName(HitActor));
			IInteractableInterface* Interface = Cast<IInteractableInterface>(HitActor);
			//Check if object is interactable
			if (Interface != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "reee");
				Interface->Execute_OnInteract(HitActor, this);
			}
			//Check if object is pickupable
			else 
			{

			}


		}

	}
}

bool AFP_Character::LineTrace()
{
	GetController()->GetPlayerViewPoint(Loc, Rot);
	Start = Loc;
	End = Start + (Rot.Vector() * TraceDistance);
	return GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);;
}

void AFP_Character::OnGrab()
{

}

void AFP_Character::OnRotate()
{

}

void AFP_Character::OnResetVR()
{
	//UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFP_Character::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void AFP_Character::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void AFP_Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFP_Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFP_Character::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	//if (TouchItem.bIsPressed == true)
	//{
	//	return;
	//}
	//if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	//{
	//	OnFire();
	//}
	//TouchItem.bIsPressed = true;
	//TouchItem.FingerIndex = FingerIndex;
	//TouchItem.Location = Location;
	//TouchItem.bMoved = false;
}

void AFP_Character::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

void AFP_Character::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	//if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
		//	{
		//		if (TouchItem.bIsPressed)
		//		{
		//			if (GetWorld() != nullptr)
		//			{
		//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
		//				if (ViewportClient != nullptr)
		//				{
		//					FVector MoveDelta = Location - TouchItem.Location;
		//					FVector2D ScreenSize;
		//					ViewportClient->GetViewportSize(ScreenSize);
		//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
		//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
		//					{
		//						TouchItem.bMoved = true;
		//						float Value = ScaledDelta.X * BaseTurnRate;
		//						AddControllerYawInput(Value);
		//					}
		//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
		//					{
		//						TouchItem.bMoved = true;
		//						float Value = ScaledDelta.Y * BaseTurnRate;
		//						AddControllerPitchInput(Value);
		//					}
		//					TouchItem.Location = Location;
		//				}
		//				TouchItem.Location = Location;
		//			}
		//		}
		//	}
}

// Called to bind functionality to input
void AFP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFP_Character::OnFire);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFP_Character::OnGrab);
	PlayerInputComponent->BindAction("Inspect", IE_Pressed, this, &AFP_Character::OnRotate);

	// Enable touchscreen input
	//EnableTouchscreenMovement(PlayerInputComponent);

	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFP_Character::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFP_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFP_Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFP_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFP_Character::LookUpAtRate);
}

bool AFP_Character::EnableTouchscreenMovement(UInputComponent* PlayerInputComponent)
{
	//if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	//{
	//	PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AFP_Character::BeginTouch);
	//	PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AFP_Character::EndTouch);

	//	//Commenting this out to be more consistent with FPS BP template.
	//	//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMaskinspeletCharacter::TouchUpdate);
	//	return true;
	//}

	return false;
}

