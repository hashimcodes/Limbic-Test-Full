// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/BuildingInterface.h"
#include "Building.generated.h"

/*From my perspective, I wanted to make an Interface called IBuilding, and each type of building
implements the interface doing different functionality but for simplicity, I will go with one 
building class with customizable properties.*/

//to manage how building will behave in different states
enum class EBuildingState : uint8
{
	EBS_UnderConstruction,
	EBS_Built,
};

UCLASS()
class LIMBIC_API ABuilding : public AActor, public IBuildingInterface
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	FString BuildingName;

	EBuildingState BuildingState;

	ABuilding();

	UFUNCTION()
	virtual void OnBuildingSelected() override;

	UFUNCTION()
	virtual void OnBuildingDeselected() override;

	UFUNCTION()
	virtual bool CanBePlaced() override;

	UFUNCTION()
	virtual void PlaceBuilding() override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere)
	bool bCollidesWithOtherBuilding = false;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* GreenMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* RedMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* BuildingColor;
};
