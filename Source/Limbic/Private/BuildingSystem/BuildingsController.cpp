// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/BuildingsController.h"
#include "BuildingSystem/Building.h"
#include "Characters/MainPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/SpringArmComponent.h"


ABuildingsController::ABuildingsController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingsController::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void ABuildingsController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BuildingToPlace)
	{
		BuildingToPlace->SetActorLocation(GetMousePlace());
	}

	if (PlayerController && PlayerController->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		OnLeftMouseClicked();
	}

	if (PlayerController && PlayerController->WasInputKeyJustPressed(EKeys::K))
	{
		DiscardBuilding();
	}
}

void ABuildingsController::OnLeftMouseClicked()
{
	if (!BuildingToPlace)
	{
		FHitResult Hit = GetMouseHit(ECollisionChannel::ECC_Pawn);
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
	} else if (BuildingToPlace && BuildingToPlace->CanBePlaced())
	{
		BuildingToPlace->PlaceBuilding();
		BuildingToPlace = nullptr;
	}
}

void ABuildingsController::DiscardBuilding()
{
	if (BuildingToPlace)
	{
		BuildingToPlace->Destroy();
	}
}

FHitResult ABuildingsController::GetMouseHit(ECollisionChannel CollisionChannel)
{
	FHitResult Hit;
	if (PlayerController)
	{
		PlayerController->GetHitResultUnderCursor(CollisionChannel, false, Hit);
	}
	return Hit;
}

FVector ABuildingsController::GetMousePlace()
{
	if (!PlayerController)
	{
		return FVector::ZeroVector;
	}
	FVector worldLocation = FVector::ZeroVector;
	FVector worldDirection = FVector::ZeroVector;
	float worldDirectionModifier = 1.f;
	PlayerController->DeprojectMousePositionToWorld(worldLocation, worldDirection);
	AMainPlayer* Player = Cast<AMainPlayer>(PlayerController->GetPawn());
	if (Player && Player->SpringArm)
	{
		worldDirectionModifier = Player->SpringArm->TargetArmLength;
	}
	FVector mouseWorldLocation = worldLocation + (worldDirection * worldDirectionModifier);
	return FVector(mouseWorldLocation.X, mouseWorldLocation.Y, 0.f);
}
