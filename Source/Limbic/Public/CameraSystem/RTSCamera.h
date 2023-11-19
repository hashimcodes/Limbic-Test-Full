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

	UFUNCTION()
	void CameraMove(const FVector2D& Value);

	UFUNCTION()
	void CameraRotation();

	UFUNCTION()
	void CameraZoom(float Value);

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
	int32 ScreenSizeX = 0;

	UPROPERTY()
	int32 ScreenSizeY = 0;

	UPROPERTY()
	class APlayerController* PlayerController = nullptr;

	UFUNCTION()
	void CameraDirectionalMove(const FVector& Direction);

	UFUNCTION()
	const FVector2D GetMousePosition();

	UFUNCTION()
	void MoveCameraOnEdges(const FVector2D& MousePosiiton);

	UFUNCTION()
	bool IsCursurOnEdges(const FVector2D& MousePosiiton);
};
