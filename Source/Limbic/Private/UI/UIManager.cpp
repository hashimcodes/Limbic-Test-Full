// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/PlacementUI.h"
#include "UI/BuildingButtonUI.h"
#include "UI/BuildingSlotUI.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "GameController.h"


AUIManager::AUIManager()
{
	PrimaryActorTick.bCanEverTick = false;

	PlacementWC = CreateDefaultSubobject<UWidgetComponent>("PlacementWidgetComponent");
	PlacementWC->SetupAttachment(GetRootComponent());

	BuildingButtonWC = CreateDefaultSubobject<UWidgetComponent>("BuildingButtonWidgetComponent");
	BuildingButtonWC->SetupAttachment(GetRootComponent());

	BuildingSlotWC = CreateDefaultSubobject<UWidgetComponent>("BuildingSlotWidgetComponent");
	BuildingSlotWC->SetupAttachment(GetRootComponent());
}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();

	PlacementUW = Cast<UPlacementUI>(PlacementWC->GetUserWidgetObject());
	BuildingButtonUW = Cast<UBuildingButtonUI>(BuildingButtonWC->GetUserWidgetObject());

	if (BuildingButtonUW)
	{
		BuildingButtonUW->AddToViewport();
		BuildingButtonUW->PlacementButton->OnClicked.AddDynamic(this, &AUIManager::ToggleBuildingsPlacement);
	}

	if (PlacementUW)
	{
		for (int i = 0; i < BuildingList.Num(); i++)
		{
			UBuildingSlotUI* BuildingSlotUW = Cast<UBuildingSlotUI>(BuildingSlotWC->GetUserWidgetObject());
			BuildingSlotUW->Building = BuildingList[i];
			PlacementUW->BuildingsListUI->AddChild(BuildingSlotUW);
		}
	}
}

void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUIManager::ToggleBuildingsPlacement()
{
	if (!bBuildingPlacementShowing)
	{
		PlacementUW->AddToViewport();
		bBuildingPlacementShowing = true;
		return;
	}

	PlacementUW->RemoveFromViewport();
	bBuildingPlacementShowing = false;
}

