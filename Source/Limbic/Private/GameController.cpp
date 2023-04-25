// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "Buildings/Building.h"


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
	//while in building mode the building following the mouse position till player place it in the world
	if (GameState == EGameState::EGS_BuildingMode && BuildingToPlace)
	{
		BuildingToPlace->SetActorLocation(GetMousePlace());
	}
}

void AGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(FName("LeftMouseClick"), IE_Pressed, this, &AGameController::OnMouseClicked);
}

FVector AGameController::GetMousePlace()
{
	FVector worldLocation;
	FVector worldDirection;
	//2D mouse position projection on 3D world
	DeprojectMousePositionToWorld(worldLocation, worldDirection);
	FVector mouseWorldLocation = worldLocation + (worldDirection * 1500.f);
	return FVector(mouseWorldLocation.X, mouseWorldLocation.Y, 0.f);
}

void AGameController::OnMouseClicked()
{
	//Mouse left button click changes it's behaviour based on game mode
	if (GameState == EGameState::EGS_BuildingMode && BuildingToPlace)
	{
		if (BuildingToPlace->CanBePlaced())
		{
			BuildingToPlace->PlaceBuilding(GetMousePlace());
			BuildingToPlace = nullptr;
			GameState = EGameState::EGS_NaviagtionMode;
		}
	}
	else if (GameState == EGameState::EGS_NaviagtionMode)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Pawn, false, Hit);

		if (Hit.bBlockingHit)
		{
			if (SelectedBuilding)
			{
				SelectedBuilding->OnBuildingDeselected();
			}
			ABuilding* building = Cast<ABuilding>(Hit.GetActor());
			if (building)
			{
				SelectedBuilding = building;
				building->OnBuildingSelected();
			}
		}
	}
}
