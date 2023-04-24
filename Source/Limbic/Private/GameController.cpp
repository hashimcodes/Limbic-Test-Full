// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "Buildings/Building.h"

AGameController::AGameController()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableTouchEvents = true;
}

void AGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(FName("LeftMouseClick"), IE_Pressed, this, &AGameController::OnMouseClicked);
}

void AGameController::OnMouseClicked()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Pawn, false, Hit);

    if (Hit.bBlockingHit)
    {
        if (SelectedBuilding)
        {
            SelectedBuilding->OnBuildingDeselected();
        }
        ABuilding* building = Cast<ABuilding>(Hit.GetActor());
        if (building)
        {
            SelectedBuilding = building;
            building->OnBuildingSelected();
        }
    }
}
