// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameController.generated.h"

enum class EGameState : uint8
{
	EGS_BuildingMode,
	EGS_NaviagtionMode
};

class ABuilding;

UCLASS()
class LIMBIC_API AGameController : public APlayerController
{
	GENERATED_BODY()

public:
	AGameController();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	EGameState GameState = EGameState::EGS_NaviagtionMode;

	UPROPERTY(VisibleAnywhere)
	ABuilding* BuildingToPlace;
	
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	ABuilding* SelectedBuilding;

	UFUNCTION()
	FVector GetMousePlace();

	UFUNCTION()
	void OnMouseClicked();
};
