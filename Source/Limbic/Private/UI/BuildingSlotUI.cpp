// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BuildingSlotUI.h"
#include "Buildings/BuildingsController.h"
#include "Buildings/Building.h"
#include "Components/Button.h"


void UBuildingSlotUI::NativeConstruct()
{
	SlotButton->OnClicked.AddDynamic(this, &UBuildingSlotUI::OnSlotButtonClicked);
	
}

void UBuildingSlotUI::OnSlotButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Slot Pressed"));
	}
	ABuilding* building = GetWorld()->SpawnActor<ABuilding>(Building);
	if (BuildingsController)
	{
		BuildingsController->BuildingToPlace = building;
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("NULL UBuildingSlotUI BuildingsController"));
		}
	}
}
