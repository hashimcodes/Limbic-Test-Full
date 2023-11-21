// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingSlotUI.generated.h"

// Forward Declarations
class UButton;
class UTextBlock;
class ABuildingsController;
class ABuilding;

UCLASS()
class LIMBIC_API UBuildingSlotUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BuildingName;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ABuildingsController> BuildingsController;

	UPROPERTY()
	TSubclassOf<ABuilding> Building;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnSlotButtonClicked();
};
