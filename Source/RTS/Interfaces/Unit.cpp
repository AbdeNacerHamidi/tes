// Fill out your copyright notice in the Description page of Project Settings.

#include "Unit.h"

// Add default functionality here for any IUnit functions that are not pure virtual.

void IUnit::Select_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("IUnit::Select_Implementation() NOT overriden!"));
}

bool IUnit::IsSelected_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("IUnit::IsSelected_Implementation() NOT overriden!"));
	return false;
}

void IUnit::Attack_Implementation(FVector AttackLocation)
{
	UE_LOG(LogTemp, Error, TEXT("IUnit::Attack_Implementation() NOT overriden!"));
}
