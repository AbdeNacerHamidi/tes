// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestructibleActor.h"
#include "RTS_DestructibleBase.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ARTS_DestructibleBase : public ADestructibleActor
{
	GENERATED_BODY()

	/** nav modifier component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class UNavModifierComponent* NavModifierComponent;

public:

	ARTS_DestructibleBase();

	virtual void PostInitializeComponents() override;

private:

	UFUNCTION()
	void OnFracture(const FVector& HitPoint, const FVector& HitDirection);

};
