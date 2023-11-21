// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BuildingSlotUI.h"
#include "BuildingSystem/BuildingsController.h"
#include "BuildingSystem/Building.h"
#include "Components/Button.h"


void UBuildingSlotUI::NativeConstruct()
{
	SlotButton->OnClicked.AddUniqueDynamic(this, &UBuildingSlotUI::OnSlotButtonClicked);
}

void UBuildingSlotUI::OnSlotButtonClicked()
{
	if (BuildingsController && BuildingsController->BuildingToPlace == nullptr)
	{
		ABuilding* building = GetWorld()->SpawnActor<ABuilding>(Building);
		BuildingsController->BuildingToPlace = building;
	}
}
