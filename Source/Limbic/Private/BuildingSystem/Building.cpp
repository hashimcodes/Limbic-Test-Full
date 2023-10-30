// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/Building.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Components/BoxComponent.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(StaticMeshComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABuilding::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABuilding::OnBoxEndOverlap);

	BuildingState = EBuildingState::EBS_UnderConstruction;

	GreenMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("GreenMaterial"));
	RedMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("RedMaterial"));
	BuildingColor = CreateDefaultSubobject<UMaterialInterface>(TEXT("BuildingColor"));
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->SetOverlayMaterial(nullptr);
}

void ABuilding::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (BuildingState == EBuildingState::EBS_UnderConstruction)
	{
		StaticMeshComponent->SetMaterial(0, RedMaterial);
	}
	bCollidesWithOtherBuilding = true;
}

void ABuilding::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//based on building state the color will back to green (if player currently building it) or blue (if it already built) 
	if (BuildingState == EBuildingState::EBS_Built) {
		StaticMeshComponent->SetMaterial(0, BuildingColor);
	}
	else
	{
		StaticMeshComponent->SetMaterial(0, GreenMaterial);
	}
	bCollidesWithOtherBuilding = false;
}

void ABuilding::OnBuildingSelected()
{
	//Can be any functionality when building is selected (openening building abilities UMG for example)
	StaticMeshComponent->SetMaterial(0, GreenMaterial);
}

void ABuilding::OnBuildingDeselected()
{
	//Can be any functionality when building is selected (closing building abilities UMG for example)
	StaticMeshComponent->SetMaterial(0, BuildingColor);
}

bool ABuilding::CanBePlaced()
{
	return !bCollidesWithOtherBuilding;
}

void ABuilding::PlaceBuilding()
{
	BuildingState = EBuildingState::EBS_Built;
	StaticMeshComponent->SetMaterial(0, BuildingColor);
}
