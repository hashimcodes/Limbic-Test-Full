// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UIManager.generated.h"

UCLASS(Abstract)
class LIMBIC_API AUIManager : public AHUD
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
	class APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere)
	class ABuildingsController* BuildingsController;

	UPROPERTY(VisibleAnywhere)
	class UPlacementUI* PlacementUW;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPlacementUI> PlacementWBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UBuildingSlotUI> BuildingSlotWBP;

	UFUNCTION()
	void OnMouseRightClicked();
};
