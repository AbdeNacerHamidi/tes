// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_DestructibleBase.h"
#include "AI/Navigation/NavModifierComponent.h"
#include "AI/Navigation/NavAreas/NavArea_Obstacle.h"
#include "DestructibleComponent.h"

ARTS_DestructibleBase::ARTS_DestructibleBase()
{
	/** nav modifier component  */
	NavModifierComponent = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifierComponent"));
}

void ARTS_DestructibleBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetDestructibleComponent()->OnComponentFracture.AddDynamic(this, &ARTS_DestructibleBase::OnFracture);
}

void ARTS_DestructibleBase::OnFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	NavModifierComponent->SetAreaClass(UNavArea_Obstacle::StaticClass());
	SetLifeSpan(3.f);
}
