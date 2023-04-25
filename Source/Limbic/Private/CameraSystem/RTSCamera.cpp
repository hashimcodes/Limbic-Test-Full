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

void ARTSCamera::MoveCamera(float DeltaTime)
{
	float mousePosX;
	float mousePosY;
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

void ARTSCamera::CameraDirectionalMove(const FVector& Direction)
{
	//alignment for axes with rotation
	FVector rotatedVector = GetActorRotation().RotateVector(Direction);
	FVector newActorLocation = GetActorLocation() + rotatedVector;
	SetActorLocation(newActorLocation);
}

void ARTSCamera::CameraZoomIn()
{
	/*float springArmLength = SpringArm->TargetArmLength;
	springArmLength -= CameraZoomSpeed;
	springArmLength = FMath::Clamp(springArmLength, ZoomMinValue, ZoomMaxValue);
	SpringArm->TargetArmLength = springArmLength;*/

	//less code and saved 4 bytes of memory
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength -= CameraZoomSpeed, ZoomMinValue, ZoomMaxValue);
}

void ARTSCamera::CameraZoomOut()
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength += CameraZoomSpeed, ZoomMinValue, ZoomMaxValue);
}

void ARTSCamera::RotateCamera(float value)
{
	if (GameController->IsInputKeyDown(EKeys::MiddleMouseButton))
	{
		float yawModifier = CameraRotationSpeed * FApp::GetDeltaTime() * value;
		FRotator newActorRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + yawModifier, GetActorRotation().Roll);
		SetActorRotation(newActorRotation);
	}
}

void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCamera(DeltaTime);
}

void ARTSCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("MouseWheelUp"), IE_Pressed, this, &ARTSCamera::CameraZoomIn);
	PlayerInputComponent->BindAction(FName("MouseWheelDown"), IE_Pressed, this, &ARTSCamera::CameraZoomOut);
	
	PlayerInputComponent->BindAxis(FName("MouseRotation"), this, &ARTSCamera::RotateCamera);
}

