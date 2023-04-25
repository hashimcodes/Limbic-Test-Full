// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BuildingSlotUI.h"
#include "GameController.h"
#include "Buildings/Building.h"
#include "Components/Button.h"


void UBuildingSlotUI::NativeConstruct()
{
	SlotButton->OnClicked.AddDynamic(this, &UBuildingSlotUI::OnSlotButtonClicked);
	GameController = Cast<AGameController>(GetOwningPlayer());
}

void UBuildingSlotUI::OnSlotButtonClicked()
{
	ABuilding* building = GetWorld()->SpawnActor<ABuilding>(Building);
	if (GameController)
	{
		GameController->BuildingToPlace = building;
		GameController->GameState = EGameState::EGS_BuildingMode;
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("No Game Controller"));
		}
	}
}
