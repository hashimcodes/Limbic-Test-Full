// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/PlacementUI.h"
#include "UI/BuildingSlotUI.h"
#include "Components/HorizontalBox.h"
#include "BuildingSystem/BuildingsController.h"
#include <Kismet/GameplayStatics.h>

AUIManager::AUIManager()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(2.f);
}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

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

void AUIManager::Tick(float DeltaTime)
{
	// can be replaced with delegate broadcast from the player controller
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

