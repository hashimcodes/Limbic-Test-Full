// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/PlacementUI.h"
#include "UI/BuildingSlotUI.h"
#include "Components/HorizontalBox.h"
#include "Buildings/BuildingsController.h"

AUIManager::AUIManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();

	PlacementUW = Cast<UPlacementUI>(CreateWidget(GetWorld(), PlacementWBP));
	if (PlacementUW)
	{
		for (int i = 0; i < BuildingList.Num(); i++)
		{
			UBuildingSlotUI* BuildingSlotUW = Cast<UBuildingSlotUI>(CreateWidget(GetWorld(), BuildingSlotWBP));
			BuildingSlotUW->BuildingsController = BuildingsController;
			BuildingSlotUW->Building = BuildingList[i];
			PlacementUW->BuildingsListUI->AddChild(BuildingSlotUW);
		}
		PlacementUW->AddToViewport();
	}
}

