// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BuildingSlotUI.h"
#include "Buildings/BuildingsController.h"
#include "Buildings/Building.h"
#include "Components/Button.h"


void UBuildingSlotUI::NativeConstruct()
{
	SlotButton->OnClicked.AddUniqueDynamic(this, &UBuildingSlotUI::OnSlotButtonClicked);
}

void UBuildingSlotUI::OnSlotButtonClicked()
{
	ABuilding* building = GetWorld()->SpawnActor<ABuilding>(Building);
	if (BuildingsController)
	{
		BuildingsController->BuildingToPlace = building;
	}
}
