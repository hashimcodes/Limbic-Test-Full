// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BuildingSlotUI.h"
#include "GameController.h"
#include "Buildings/Building.h"
#include "Components/Button.h"


void UBuildingSlotUI::SetOnclickListener()
{
	SlotButton->OnClicked.AddDynamic(this, &UBuildingSlotUI::OnSlotButtonClicked);
}

void UBuildingSlotUI::OnSlotButtonClicked()
{
	ABuilding* building = GetWorld()->SpawnActor<ABuilding>(Building);
	GameController->BuildingToPlace = building;
	GameController->GameState = EGameState::EGS_BuildingMode;
}
