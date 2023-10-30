// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildingInterface.generated.h"

UINTERFACE(MinimalAPI)
class UBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

class LIMBIC_API IBuildingInterface
{
	GENERATED_BODY()

public:
	virtual void OnBuildingSelected() = 0;

	virtual void OnBuildingDeselected() = 0;

	virtual bool CanBePlaced() = 0;

	virtual void PlaceBuilding() = 0;
};
