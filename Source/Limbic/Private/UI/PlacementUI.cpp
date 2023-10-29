// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlacementUI.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

void UPlacementUI::NativeConstruct()
{
	Super::NativeConstruct();
	if (BuildingsListUI->GetParent())
	{
		BuildingsListUI->GetParent()->SetIsEnabled(false);
		BuildingsListUI->GetParent()->SetVisibility(ESlateVisibility::Hidden);
	}

	if (PlacementButton)
	{
		PlacementButton->OnClicked.AddUniqueDynamic(this, &UPlacementUI::OnPlacementButtonClicked);
	}
}

void UPlacementUI::OnPlacementButtonClicked()
{
	if (BuildingsListUI->GetParent()->GetIsEnabled())
	{
		BuildingsListUI->GetParent()->SetIsEnabled(false);
		BuildingsListUI->GetParent()->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		BuildingsListUI->GetParent()->SetIsEnabled(true);
		BuildingsListUI->GetParent()->SetVisibility(ESlateVisibility::Visible);
	}
}

