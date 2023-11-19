// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSController.generated.h"

// Forward Declerations
class ARTSCamera;
class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(Abstract)
class LIMBIC_API ARTSController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputAction* ActionRotate = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputAction* ActionZoom = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputMappingContext* InputMappingContext = nullptr;

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleRotate();
	void HandleZoom(const FInputActionValue& InputActionValue);

private:
	UPROPERTY()
	ARTSCamera* RTSPlayer = nullptr;

	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;
	
};
