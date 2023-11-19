// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraSystem/RTSCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ARTSCamera::ARTSCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComp);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArm);
}

void ARTSCamera::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->GetViewportSize(ScreenSizeX, ScreenSizeY);
	}
}

void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector2D mousePosition = GetMousePosition();
	if (IsCursurOnEdges(mousePosition))
	{
		MoveCameraOnEdges(mousePosition);
	}
}

const FVector2D ARTSCamera::GetMousePosition()
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

bool ARTSCamera::IsCursurOnEdges(const FVector2D& MousePosiiton)
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

void ARTSCamera::MoveCameraOnEdges(const FVector2D& MousePosiiton)
{
	FVector xAxisDirection = FVector(0.f, CameraMoveSpeed * FApp::GetDeltaTime(), 0.f);
	FVector yAxisDirection = FVector(CameraMoveSpeed * FApp::GetDeltaTime(), 0.f, 0.f);

	//Left and Right
	if (MousePosiiton.X <= CameraEdgesMargin)
	{
		CameraDirectionalMove(-xAxisDirection);
	}
	if (MousePosiiton.X >= ScreenSizeX - CameraEdgesMargin)
	{
		CameraDirectionalMove(xAxisDirection);
	}
	//Top and Down
	if (MousePosiiton.Y <= CameraEdgesMargin)
	{	
		CameraDirectionalMove(yAxisDirection);
	}
	if (MousePosiiton.Y >= ScreenSizeY - CameraEdgesMargin)
	{
		CameraDirectionalMove(-yAxisDirection);
	}
}

void ARTSCamera::CameraMove(const FVector2D& Value)
{
	FVector xAxisDirection = FVector(0.f, CameraMoveSpeed * FApp::GetDeltaTime(), 0.f);
	FVector yAxisDirection = FVector(CameraMoveSpeed * FApp::GetDeltaTime(), 0.f, 0.f);
	CameraDirectionalMove(Value.X * xAxisDirection);
	CameraDirectionalMove(Value.Y * yAxisDirection);
}

void ARTSCamera::CameraDirectionalMove(const FVector& Direction)
{
	FVector rotatedVector = GetActorRotation().RotateVector(Direction);
	FVector newActorLocation = GetActorLocation() + rotatedVector;
	SetActorLocation(newActorLocation);
}

void ARTSCamera::CameraRotation()
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
		PlayerController->GetInputMouseDelta(mouseDeltaX, mouseDeltaY);
		PlayerController->GetMousePosition(mousePosX, mousePosY);
	}
	if (abs(mousePosX - middleScreenSizeX) < 20 || abs(mousePosY - middleScreenSizeY) < 20)
	{
		return;
	}
	if (mousePosX < middleScreenSizeX && mousePosY < middleScreenSizeY)
	{
		mouseDelta = -mouseDeltaX - mouseDeltaY;
	}
	if (mousePosX > middleScreenSizeX && mousePosY < middleScreenSizeY)
	{
		mouseDelta = -mouseDeltaX + mouseDeltaY;
	}
	if (mousePosX < middleScreenSizeX && mousePosY > middleScreenSizeY)
	{
		mouseDelta = mouseDeltaX - mouseDeltaY;
	}
	if (mousePosX > middleScreenSizeX && mousePosY > middleScreenSizeY)
	{
		mouseDelta = mouseDeltaX + mouseDeltaY;
	}
	float yawModifier = CameraRotationSpeed * FApp::GetDeltaTime() * mouseDelta;
	FRotator newActorRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + yawModifier, GetActorRotation().Roll);
	SetActorRotation(newActorRotation);
}

void ARTSCamera::CameraZoom(float Value)
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength -= (Value * CameraZoomSpeed), ZoomMinValue, ZoomMaxValue);
}
