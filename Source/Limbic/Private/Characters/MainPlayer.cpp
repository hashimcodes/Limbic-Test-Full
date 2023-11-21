// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		PlayerController->GetViewportSize(ScreenSizeX, ScreenSizeY);
	}
}

void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector2D mousePosition = GetMousePosition();
	if (IsCursurOnEdges(mousePosition))
	{
		MoveEdges(mousePosition);
	}
}

void AMainPlayer::Move(const FVector2D& Value)
{
	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector DirectionX = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		const FVector DirectionY = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// Speed depending on MovementComponent speed parms
		AddMovementInput(DirectionX, Value.X);
		AddMovementInput(DirectionY, Value.Y);
	}
}

const FVector2D AMainPlayer::GetMousePosition()
{
	float mousePosX = 0.f;
	float mousePosY = 0.f;
	if (PlayerController)
	{
		PlayerController->GetMousePosition(mousePosX, mousePosY);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Null Player Controller"));
		}
		return FVector2D(0.f, 0.f);
	}
	return FVector2D(mousePosX, mousePosY);
}

bool AMainPlayer::IsCursurOnEdges(const FVector2D& MousePosiiton)
{
	if (MousePosiiton == FVector2D::ZeroVector)
	{
		return false;
	}
	return MousePosiiton.X <= CameraEdgesMargin ||
		MousePosiiton.X >= ScreenSizeX - CameraEdgesMargin ||
		MousePosiiton.Y <= CameraEdgesMargin ||
		MousePosiiton.Y >= ScreenSizeY - CameraEdgesMargin;
}

void AMainPlayer::MoveEdges(const FVector2D& MousePosiiton)
{
	float x = 0.f;
	float y = 0.f;
	if (MousePosiiton.X <= CameraEdgesMargin)
	{
		x = -1;
	}
	if (MousePosiiton.X >= ScreenSizeX - CameraEdgesMargin)
	{
		x = 1;
	}
	if (MousePosiiton.Y <= CameraEdgesMargin)
	{
		y = 1;
	}
	if (MousePosiiton.Y >= ScreenSizeY - CameraEdgesMargin)
	{
		y = -1;
	}
	Move(FVector2D(x, y));
}

void AMainPlayer::Rotate()
{
	float mousePosX = 0.f;
	float mousePosY = 0.f;
	float mouseDeltaX = 0.f;
	float mouseDeltaY = 0.f;
	float mouseDelta = 0.f;
	float middleScreenSizeX = ScreenSizeX / static_cast<float>(2);
	float middleScreenSizeY = ScreenSizeY / static_cast<float>(2);

	if (PlayerController)
	{
		PlayerController->GetMousePosition(mousePosX, mousePosY);
		PlayerController->GetInputMouseDelta(mouseDeltaX, mouseDeltaY);
	}
	if (abs(mousePosX - middleScreenSizeX) < 20 || abs(mousePosY - middleScreenSizeY) < 20)
	{
		return;
	}
	if (mousePosX < middleScreenSizeX && mousePosY < middleScreenSizeY) //1
	{
		mouseDelta = -mouseDeltaX - mouseDeltaY;
	}
	if (mousePosX > middleScreenSizeX && mousePosY < middleScreenSizeY) //2
	{
		mouseDelta = -mouseDeltaX + mouseDeltaY;
	}
	if (mousePosX < middleScreenSizeX && mousePosY > middleScreenSizeY) //3
	{
		mouseDelta = mouseDeltaX - mouseDeltaY;
	}
	if (mousePosX > middleScreenSizeX && mousePosY > middleScreenSizeY) //4
	{
		mouseDelta = mouseDeltaX + mouseDeltaY;
	}
	AddControllerYawInput(mouseDelta * CameraRotationSpeed * FApp::GetDeltaTime());
}

void AMainPlayer::Zoom(float Value)
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength -= (Value * CameraZoomSpeed), ZoomMinValue, ZoomMaxValue);
}
