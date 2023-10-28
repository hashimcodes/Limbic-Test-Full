// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingSlotUI.generated.h"

UCLASS()
class LIMBIC_API UBuildingSlotUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* SlotButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BuildingName;

	UPROPERTY(EditAnywhere)
	class ABuildingsController* BuildingsController;

	UPROPERTY()
	TSubclassOf<class ABuilding> Building;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnSlotButtonClicked();
};
