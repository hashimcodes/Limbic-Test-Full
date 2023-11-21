// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingsController.generated.h"

class ABuilding;
class APlayerController;

UCLASS()
class LIMBIC_API ABuildingsController : public AActor
{
	GENERATED_BODY()

public:
	ABuildingsController();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABuilding> BuildingToPlace;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABuilding> SelectedBuilding;

	UFUNCTION()
	void OnLeftMouseClicked();

	UFUNCTION()
	void DiscardBuilding();

	UFUNCTION()
	FHitResult GetMouseHit(ECollisionChannel CollisionChannel);

	UFUNCTION()
	FVector GetMousePlace();
};
