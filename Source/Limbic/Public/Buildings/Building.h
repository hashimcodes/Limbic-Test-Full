// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

/*From my perspective, I wanted to make an Interface called IBuilding, and each type of building
implements the interface doing different functionality but for simplicity, I will go with one 
building class with customizable properties.*/

//to manage how building will behave in different states
enum class EBuildingState : uint8
{
	EBS_NotYetBuilt,
	EBS_Built,
	EBS_Selected
};

//in case we want to sort or make categories based on buildings types
enum class EBuildingType : uint8
{
	EBT_Resource,
	EBT_Army,
	EBT_Decor
};

UCLASS()
class LIMBIC_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	FString BuildingName;

	//UPROPERTY(VisibleAnywhere)
	EBuildingState BuildingState = EBuildingState::EBS_NotYetBuilt;

	//UPROPERTY(VisibleAnywhere)
	EBuildingType BuildingType;

	ABuilding();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool AreRequirmentsFulfilled();

	UFUNCTION()
	void OnBuildingSelected();

	UFUNCTION()
	void OnBuildingDeselected();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* GreenMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* RedMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* BlueMaterial;
};
