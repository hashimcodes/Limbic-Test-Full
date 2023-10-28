// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSCamera.generated.h"

UCLASS()
class LIMBIC_API ARTSCamera : public APawn
{
	GENERATED_BODY()

public:
	ARTSCamera();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Props")
	float CameraMoveSpeed = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Props")
	float CameraEdgesMargin = 40.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Props")
	float ZoomMaxValue = 1500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Props")
	float ZoomMinValue = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Props")
	float CameraZoomSpeed = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Props")
	float CameraRotationSpeed = 200.f;

	UPROPERTY()
	int32 ScreenSizeX;

	UPROPERTY()
	int32 ScreenSizeY;

	UPROPERTY()
	class AGameController* GameController;

	UFUNCTION()
	void CameraDirectionalMove(const FVector& Direction);

	UFUNCTION()
	void MoveCameraOnEdges(float DeltaTime);

	UFUNCTION()
	void CameraMoveOnX(float Value);

	UFUNCTION()
	void CameraMoveOnY(float Value);

	UFUNCTION()
	void CameraZoomHandler(float Value);

	UFUNCTION()
	void RotateCamera(float DeltaTime);
};
