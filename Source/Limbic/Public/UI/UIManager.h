// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UIManager.generated.h"

class UWidgetComponent;

UCLASS()
class LIMBIC_API AUIManager : public APawn
{
	GENERATED_BODY()
	
public:	
	AUIManager();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class ABuilding>> BuildingList;


protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PlacementWC;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* BuildingButtonWC;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* BuildingSlotWC;

	UPROPERTY(VisibleAnywhere)
	class UPlacementUI* PlacementUW;

	UPROPERTY(VisibleAnywhere)
	class UBuildingButtonUI* BuildingButtonUW;

	UPROPERTY()
	bool bBuildingPlacementShowing = false;

	UFUNCTION()
	void ToggleBuildingsPlacement();

	UFUNCTION()
	void Building();
};
