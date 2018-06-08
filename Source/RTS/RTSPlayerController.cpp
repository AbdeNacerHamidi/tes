// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RTSPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "RTSCharacter.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "ConstructorHelpers.h"
#include "RTS/UI/RTS_HUD.h"
#include "Kismet/GameplayStatics.h"

ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	/**  set material */
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialTemplate(TEXT("/Game/TopDownCPP/Blueprints/M_Cursor_Decal_Inst_Red"));
	if (MaterialTemplate.Succeeded())
	{
		ActionDecal = MaterialTemplate.Object;
	}

	/**  set the hud widget asset */
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetClassBPClass(TEXT("/Game/TopDownCPP/Blueprints/UI/WBP_HUD"));
	if (HUDWidgetClassBPClass.Class)
	{
		HUDWidgetClass = HUDWidgetClassBPClass.Class;
	}
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUD_Widget = CreateWidget<URTS_HUD>(GetWorld(), HUDWidgetClass);
		if (HUD_Widget)
		{
			HUD_Widget->AddToViewport(); 
			HUD_Widget->SetPC(this);
		}
	}

	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
}

void ARTSPlayerController::SetupInputComponent()
{
	// set up game play key bindings
	Super::SetupInputComponent();

	/** action  */
	InputComponent->BindAction("Action", IE_Pressed, this, &ARTSPlayerController::Action);

	/** select  */
	InputComponent->BindAction("Select", IE_Pressed, this, &ARTSPlayerController::SelectUnitUnderCursor);
}

void ARTSPlayerController::Action()
{
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		/** spawn decal  */
		SpawnDecalAtActionLocation();

		/** move selected units to location  */
		for (AActor* Unit : SelectedUnits)
		{
			if (APawn* Pawn = Cast<APawn>(Unit))
			{
				if (AAIController* AIC = Cast<AAIController>(Pawn->GetController()))
				{
					if (bSelectedUnitsShouldAttack)
					{
						if (Pawn->GetClass()->ImplementsInterface(UUnit::StaticClass()))
						{
							IUnit::Execute_Attack(Pawn, Hit.Location);
						}
					} 
					else
					{
						AIC->StopMovement();
						AIC->MoveToLocation(Hit.Location);
					}
				}
			}
		}
	}

	if (bSelectedUnitsShouldAttack)
	{
		bSelectedUnitsShouldAttack = false;

		/** reset attack checkbox  */
		if (HUD_Widget)
		{
			HUD_Widget->ResetAttack();
		}
	}
}

void ARTSPlayerController::SelectUnitUnderCursor()
{
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		if (AActor* SelectedActor = Hit.GetActor())
		{
			SelectUnit(SelectedActor);
		}
	}
}

void ARTSPlayerController::SelectUnit(AActor* SelectedActor)
{
	if (SelectedActor->GetClass()->ImplementsInterface(UUnit::StaticClass()))
	{
		IUnit::Execute_Select(SelectedActor);
		if (IUnit::Execute_IsSelected(SelectedActor))
		{
			SelectedUnits.AddUnique(SelectedActor);
		}
		else
		{
			SelectedUnits.Remove(SelectedActor);
		}

		UpdateSelectedUnitsInHUD();
	}
}

void ARTSPlayerController::UpdateSelectedUnitsInHUD()
{
	FString String = FString::FromInt(SelectedUnits.Num());
	NumberOfSelectedUntis = FText::FromString(String);
	if (HUD_Widget)
	{
		HUD_Widget->PlayAnim();
	}
}

void ARTSPlayerController::SpawnDecalAtActionLocation()
{
	if (SelectedUnits.Num() > 0)
	{
		if (LastDecal)
		{
			LastDecal->DestroyComponent();
			LastDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ActionDecal, DecalSize, Hit.Location, FRotator(-90.f, 0.f, 0.f), 1.f);
		}
		else
		{
			LastDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ActionDecal, DecalSize, Hit.Location, FRotator(-90.f, 0.f, 0.f), 1.f);
		}
	}
}

void ARTSPlayerController::SelectAllUnits()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UUnit::StaticClass(), FoundActors);
	
	for (AActor* Actor : FoundActors)
	{
		if (!IUnit::Execute_IsSelected(Actor))
		{
			IUnit::Execute_Select(Actor);
			SelectedUnits.AddUnique(Actor);
		}
	}

	UpdateSelectedUnitsInHUD();
}

void ARTSPlayerController::DeselectAllUnits()
{
	for (AActor* Actor : SelectedUnits)
	{
		if (IUnit::Execute_IsSelected(Actor))
		{
			IUnit::Execute_Select(Actor);
		}
	}

	SelectedUnits.Empty();

	UpdateSelectedUnitsInHUD();
}
