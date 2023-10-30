// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BuildingsController.generated.h"

class ABuilding;

UCLASS()
class LIMBIC_API ABuildingsController : public APawn
{
	GENERATED_BODY()

public:
	ABuildingsController();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	ABuilding* BuildingToPlace;

	UPROPERTY(VisibleAnywhere)
	class UPlacementUI* PlacementUI;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere)
	ABuilding* SelectedBuilding;

	UFUNCTION()
	void OnMouseClicked();

	UFUNCTION()
	void DiscardBuilding();

	UFUNCTION()
	FHitResult GetMouseHit();

	UFUNCTION()
	FVector GetMousePlace();
};
