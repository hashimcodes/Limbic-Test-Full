// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlacementUI.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

void UPlacementUI::NativeConstruct()
{
	Super::NativeConstruct();

	BuildingsListUI->GetParent()->SetVisibility(ESlateVisibility::Collapsed);

	if (PlacementButton)
	{
		PlacementButton->OnClicked.AddUniqueDynamic(this, &UPlacementUI::OnPlacementButtonClicked);
	}
}

void UPlacementUI::OnPlacementButtonClicked()
{
	BuildingsListUI->GetParent()->SetVisibility(ESlateVisibility::Visible);
}

