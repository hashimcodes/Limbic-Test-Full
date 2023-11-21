// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UIManager.generated.h"

// Forward Declarations
class ABuilding;
class APlayerController;
class ABuildingsController;
class UPlacementUI;
class UBuildingSlotUI;

UCLASS(Abstract)
class LIMBIC_API AUIManager : public AHUD
{
	GENERATED_BODY()
	
public:	
	AUIManager();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ABuilding>> BuildingList;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABuildingsController> BuildingsController;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlacementUI> PlacementUW;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlacementUI> PlacementWBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBuildingSlotUI> BuildingSlotWBP;

	UFUNCTION()
	void OnMouseRightClicked();
};
