// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

UCLASS()
class LIMBIC_API AUIManager : public AActor
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
	class UPlacementUI* PlacementUW;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlacementUI> PlacementWBP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBuildingSlotUI> BuildingSlotWBP;

	UPROPERTY(EditAnywhere)
	class ABuildingsController* BuildingsController;

	UFUNCTION()
	void OnMouseRightClicked();
};
