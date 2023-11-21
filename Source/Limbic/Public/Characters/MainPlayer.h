// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APlayerController;

UCLASS()
class LIMBIC_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AMainPlayer();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Move(const FVector2D& Value);

	UFUNCTION()
	void Rotate();

	UFUNCTION()
	void Zoom(float Value);

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

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
	APlayerController* PlayerController = nullptr;

	UFUNCTION()
	const FVector2D GetMousePosition();

	UFUNCTION()
	void MoveEdges(const FVector2D& MousePosition);

	UFUNCTION()
	bool IsCursurOnEdges(const FVector2D& MousePosition);
};
