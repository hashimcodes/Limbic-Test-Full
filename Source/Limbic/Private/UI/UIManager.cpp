// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/PlacementUI.h"
#include "UI/BuildingSlotUI.h"
#include "Components/HorizontalBox.h"
#include "Buildings/BuildingsController.h"
#include <Kismet/GameplayStatics.h>

AUIManager::AUIManager()
{
	PrimaryActorTick.bCanEverTick = true;
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
	
	if (PlayerController && PlayerController->WasInputKeyJustPressed(EKeys::RightMouseButton))
	{
		OnMouseRightClicked();
	}
}

void AUIManager::OnMouseRightClicked()
{
	if (PlacementUW)
	{
		if (PlacementUW->BuildingsListUI->GetParent()->GetIsEnabled())
		{
			PlacementUW->BuildingsListUI->GetParent()->SetIsEnabled(false);
			PlacementUW->BuildingsListUI->GetParent()->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

