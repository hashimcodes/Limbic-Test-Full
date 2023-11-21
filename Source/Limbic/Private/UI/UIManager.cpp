// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/PlacementUI.h"
#include "UI/BuildingSlotUI.h"
#include "Components/HorizontalBox.h"
#include "BuildingSystem/BuildingsController.h"

AUIManager::AUIManager()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(2.f);
}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetOwningPlayerController();
	BuildingsController = GetWorld()->SpawnActor<ABuildingsController>();
	PlacementUW = Cast<UPlacementUI>(CreateWidget(GetWorld(), PlacementWBP));
	if (PlacementUW)
	{
		for (auto& building : BuildingList)
		{
			UBuildingSlotUI* BuildingSlotUW = Cast<UBuildingSlotUI>(CreateWidget(GetWorld(), BuildingSlotWBP));
			BuildingSlotUW->BuildingsController = BuildingsController;
			BuildingSlotUW->Building = building;
			PlacementUW->BuildingsListUI->AddChild(BuildingSlotUW);
		}
		PlacementUW->AddToViewport();
	}
}

void AUIManager::Tick(float DeltaTime)
{
	// can be replaced with delegate broadcast from the player controller
	// or having reference for this in player controller then I can bind this function
	if (PlayerController && PlayerController->WasInputKeyJustPressed(EKeys::RightMouseButton))
	{
		OnMouseRightClicked();
	}
}

void AUIManager::OnMouseRightClicked()
{
	if (PlacementUW)
	{
		PlacementUW->BuildingsListUI->GetParent()->SetVisibility(ESlateVisibility::Collapsed);
	}
}

