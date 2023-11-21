// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/RTSController.h"
#include "Characters/MainPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"

ARTSController::ARTSController()
{
	bShowMouseCursor = true;
}

void ARTSController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	
	MainPlayer = Cast<AMainPlayer>(aPawn);
	checkf(MainPlayer, TEXT("Player is null"));

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("EnhancedInputComponent is null"));

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("InputSubsystem is null"));
	checkf(InputMappingContext, TEXT("InputMappingContext is null"));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	if (ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &ARTSController::HandleMove);
	}

	if (ActionRotate)
	{
		EnhancedInputComponent->BindAction(ActionRotate, ETriggerEvent::Triggered, this, &ARTSController::HandleRotate);

	}

	if (ActionZoom)
	{
		EnhancedInputComponent->BindAction(ActionZoom, ETriggerEvent::Triggered, this, &ARTSController::HandleZoom);

	}
}

void ARTSController::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();
	Super::OnUnPossess();
}

void ARTSController::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	if (MainPlayer)
	{
		MainPlayer->Move(MovementVector);
	}
}

void ARTSController::HandleRotate()
{
	if (MainPlayer)
	{
		MainPlayer->Rotate();
	}
}

void ARTSController::HandleZoom(const FInputActionValue& InputActionValue)
{
	const float ZoomValue = InputActionValue.Get<float>();
	if (MainPlayer)
	{
		MainPlayer->Zoom(ZoomValue);
	}
}
 