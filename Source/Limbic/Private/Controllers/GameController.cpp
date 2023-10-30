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