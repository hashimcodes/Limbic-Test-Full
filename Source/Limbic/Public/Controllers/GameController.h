// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameController.generated.h"

UCLASS()
class LIMBIC_API AGameController : public APlayerController
{
	GENERATED_BODY()

public:
	AGameController();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(VisibleAnywhere)
	class UPlacementUI* PlacementUI;

	UFUNCTION()
	FHitResult GetMouseHit();

	UFUNCTION()
	FVector GetMousePlace();

private:
	UFUNCTION()
	void OnMouseClicked();
};
