// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Unit.h"
#include "RTSCharacter.generated.h"

UCLASS(Blueprintable)
class ARTSCharacter : public ACharacter, public IUnit
{
	GENERATED_BODY()

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

public:

	ARTSCharacter();

	//~ Begin IUnit Interface

	/** called when player select object that implements this interface  */
	virtual void Select_Implementation() override;

	/** returns whether this unit is selected or not */
	virtual bool IsSelected_Implementation() override;

	//~ End  IUnit Interface

private:

	/** shows whether this guy is selected or not  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bSelected : 1;

public:

	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
};

