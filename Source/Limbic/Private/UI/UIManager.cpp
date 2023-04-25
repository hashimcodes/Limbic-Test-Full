// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/PlacementUI.h"
#include "UI/BuildingButtonUI.h"
#include "UI/BuildingSlotUI.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Controllers/GameController.h"
#include "Kismet/GameplayStatics.h"

AUIManager::AUIManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();

	PlacementUW = Cast<UPlacementUI>(CreateWidget(GetWorld(), PlacementWBP));
	BuildingButtonUW = Cast<UBuildingButtonUI>(CreateWidget(GetWorld(), BuildingButtonWBP));

	if (BuildingButtonUW)
	{
		BuildingButtonUW->AddToViewport();
		BuildingButtonUW->PlacementButton->OnClicked.AddDynamic(this, &AUIManager::ToggleBuildingsPlacement);
	}

	if (PlacementUW)
	{
		GameController = Cast<AGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (GameController)
		{
			GameController->PlacementUI = PlacementUW;
		}

		for (int i = 0; i < BuildingList.Num(); i++)
		{
			UBuildingSlotUI* BuildingSlotUW = Cast<UBuildingSlotUI>(CreateWidget(GetWorld(), BuildingSlotWBP));
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
	if (PlacementUW->IsInViewport())
	{
		PlacementUW->RemoveFromViewport();
	}
	else
	{
		PlacementUW->AddToViewport();
	}
}

