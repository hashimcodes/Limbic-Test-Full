// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/BuildingInterface.h"
#include "Building.generated.h"

// Forward Declerations
class ABuilding;
class UStaticMeshComponent;
class UBoxComponent;
class UMaterialInterface;

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
	TArray<TObjectPtr<ABuilding>> CurrentCollidingBuildings;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* GreenMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* RedMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* BuildingColor;
};
