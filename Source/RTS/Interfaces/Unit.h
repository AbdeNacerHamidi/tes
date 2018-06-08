// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Unit.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UUnit : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_API IUnit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	/** called when player select object that implements this interface  */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Unit Interface")
	void Select();
	virtual void Select_Implementation();

	/** returns whether this unit is selected or not */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Unit Interface")
	bool IsSelected();
	virtual bool IsSelected_Implementation();

	/** called when selected units intended to attack  */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Unit Interface")
	void Attack(FVector AttackLocation);
	virtual void Attack_Implementation(FVector AttackLocation);
};
