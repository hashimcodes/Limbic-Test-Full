// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/GameController.h"
#include "UI/PlacementUI.h"

AGameController::AGameController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
}

void AGameController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FHitResult AGameController::GetMouseHit()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Pawn, false, Hit);
	return Hit;
}

FVector AGameController::GetMousePlace()
{
	FVector worldLocation;
	FVector worldDirection;
	DeprojectMousePositionToWorld(worldLocation, worldDirection);
	FVector mouseWorldLocation = worldLocation + (worldDirection * 1500.f);
	return FVector(mouseWorldLocation.X, mouseWorldLocation.Y, 0.f);
}

void AGameController::OnMouseClicked()
{
	if (GEngine)
	{
		FVector mousePlaceVector = GetMousePlace();
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("GetMousePlace: %f %f %f"), mousePlaceVector.X, mousePlaceVector.Y, mousePlaceVector.Y));
	}
	FHitResult Hit = GetMouseHit();

	if (Hit.bBlockingHit)
	{
		if (PlacementUI && PlacementUI->IsInViewport())
		{
			PlacementUI->RemoveFromViewport();
		}
	}
}

void AGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction(FName("LeftMouseClick"), IE_Pressed, this, &AGameController::OnMouseClicked);
}
