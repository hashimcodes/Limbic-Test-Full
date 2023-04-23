// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/Building.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(StaticMeshComponent);

	GreenMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("GreenMaterial"));
	RedMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("RedMaterial"));
	BlueMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("BlueMaterial"));

}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->SetMaterial(0, RedMaterial);
	StaticMeshComponent->SetOverlayMaterial(nullptr);
	
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

bool ABuilding::AreRequirmentsFulfilled()
{
	return false;
}

void ABuilding::OnBuildingSelected()
{
	StaticMeshComponent->SetMaterial(0, GreenMaterial);
}

