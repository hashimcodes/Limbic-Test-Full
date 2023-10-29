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
