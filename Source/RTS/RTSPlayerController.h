// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

UCLASS()
class ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	/** action decal material asset  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* ActionDecal;

public:

	ARTSPlayerController();

	virtual void BeginPlay() override;

protected:

	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void SetupInputComponent() override;
	// End PlayerController interface
	
private:

	/** called to handle action for all selected units  */
	void Action();

	/** called to select/deselect unit under the cursor  */
	void SelectUnitUnderCursor();

	/** called to select/deselect single unit  */
	void SelectUnit(AActor* SelectedActor);

	void UpdateSelectedUnitsInHUD();

	/** called to spawn a hint decal at action location  */
	void SpawnDecalAtActionLocation();

	/** called to select all units with Unit interface */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SelectAllUnits();

	/** called to deselect all units with Unit interface */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void DeselectAllUnits();

	// -----------------------------------------------------------------------------------
	
	/** hud widget class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class URTS_HUD> HUDWidgetClass;

	/** hud reference */
	UPROPERTY()
	class URTS_HUD* HUD_Widget;

	/** all selected units  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TArray<class AActor*> SelectedUnits;

	/** decal size  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	FVector DecalSize = FVector(64.f, 64.f, 64.f);

	/** last cached decal */
	UPROPERTY()
	UDecalComponent* LastDecal;

	/** mouse click hit result  */
	UPROPERTY()
	FHitResult Hit;

	/** shows whether is  or not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bSelectedUnitsShouldAttack : 1;

	/** shows how many units are selected right now  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	FText NumberOfSelectedUntis = FText::FromString("0");

};


