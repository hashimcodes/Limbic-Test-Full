// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraSystem/RTSCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Controllers/GameController.h"

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
	GameController = Cast<AGameController>(GetController());
	if (GameController)
	{
		GameController->GetViewportSize(ScreenSizeX, ScreenSizeY);
	}
}

void ARTSCamera::MoveCameraOnEdges(float DeltaTime)
{
	float mousePosX{};
	float mousePosY{};
	FVector xAxisDirection = FVector(0.f, CameraMoveSpeed * DeltaTime, 0.f);
	FVector yAxisDirection = FVector(CameraMoveSpeed * DeltaTime, 0.f, 0.f);

	if (GameController)
	{
		GameController->GetMousePosition(mousePosX, mousePosY);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Null Player Controller"));
		}
	}

	//Left and Right
	if (mousePosX <= CameraEdgesMargin)
	{
		CameraDirectionalMove(-xAxisDirection);
	}
	if (mousePosX >= ScreenSizeX - CameraEdgesMargin)
	{
		CameraDirectionalMove(xAxisDirection);
	}
	//Top and Down
	if (mousePosY <= CameraEdgesMargin)
	{	
		CameraDirectionalMove(yAxisDirection);
	}
	if (mousePosY >= ScreenSizeY - CameraEdgesMargin)
	{
		CameraDirectionalMove(-yAxisDirection);
	}
}

void ARTSCamera::CameraMoveOnX(float Value)
{
	if (Value == 0) return;
	FVector xAxisDirection = FVector(0.f, CameraMoveSpeed * FApp::GetDeltaTime(), 0.f);
	CameraDirectionalMove(Value * xAxisDirection);
}

void ARTSCamera::CameraMoveOnY(float Value)
{
	if (Value == 0) return;
	FVector yAxisDirection = FVector(CameraMoveSpeed * FApp::GetDeltaTime(), 0.f, 0.f);
	CameraDirectionalMove(Value * yAxisDirection);
}

void ARTSCamera::CameraZoomHandler(float Value)
{
	if (Value == 0) return;
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength -= (Value * CameraZoomSpeed), ZoomMinValue, ZoomMaxValue);
}

void ARTSCamera::CameraDirectionalMove(const FVector& Direction)
{
	FVector rotatedVector = GetActorRotation().RotateVector(Direction);
	FVector newActorLocation = GetActorLocation() + rotatedVector;
	SetActorLocation(newActorLocation);
}

void ARTSCamera::RotateCamera(float DeltaTime)
{
	float mousePosX;
	float mousePosY;
	GameController->GetMousePosition(mousePosX, mousePosY);
	float middleScreenSizeX = ScreenSizeX / static_cast<float>(2);
	float middleScreenSizeY = ScreenSizeY / static_cast<float>(2);
	if (abs(mousePosX - middleScreenSizeX) < 20 || abs(mousePosY - middleScreenSizeY) < 20) return;
	float mouseDeltaX;
	float mouseDeltaY;
	GameController->GetInputMouseDelta(mouseDeltaX, mouseDeltaY);
	float mouseDelta{};
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
	float yawModifier = CameraRotationSpeed * DeltaTime * mouseDelta;
	FRotator newActorRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + yawModifier, GetActorRotation().Roll);
	SetActorRotation(newActorRotation);
}

void ARTSCamera::OnMouseClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("OnMouseClicked"));
	}
}

void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCameraOnEdges(DeltaTime);
	if (GameController->IsInputKeyDown(EKeys::ThumbMouseButton2))
	{
		RotateCamera(DeltaTime);
	}
}

void ARTSCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("LeftRight"), this, &ARTSCamera::CameraMoveOnX);
	PlayerInputComponent->BindAxis(FName("UpDown"), this, &ARTSCamera::CameraMoveOnY);
	PlayerInputComponent->BindAxis(FName("MouseWheel"), this, &ARTSCamera::CameraZoomHandler);
	//PlayerInputComponent->BindAction(FName("E"), IE_Pressed, this, &ARTSCamera::OnMouseClicked);
}

