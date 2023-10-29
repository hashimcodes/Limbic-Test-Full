// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BuildingsController.h"
#include "Controllers/GameController.h"
#include "Buildings/Building.h"
#include <Kismet/GameplayStatics.h>

ABuildingsController::ABuildingsController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingsController::BeginPlay()
{
	Super::BeginPlay();
	GameController = Cast<AGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ABuildingsController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BuildingToPlace)
	{
		if (GameController)
		{
			BuildingToPlace->SetActorLocation(GameController->GetMousePlace());
		}
	}

	if (GameController && GameController->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		OnMouseClicked();
	}

	if (GameController && GameController->WasInputKeyJustPressed(EKeys::RightMouseButton))
	{
		DiscardBuilding();
	}
}

void ABuildingsController::OnMouseClicked()
{
	if (BuildingToPlace && BuildingToPlace->CanBePlaced())
	{
		BuildingToPlace->PlaceBuilding();
		BuildingToPlace = nullptr;
	}

	FHitResult Hit;
	if (GameController)
	{
		Hit = GameController->GetMouseHit();
	}
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

void ABuildingsController::DiscardBuilding()
{
	if (BuildingToPlace)
	{
		BuildingToPlace->Destroy();
	}
}


void ABuildingsController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

