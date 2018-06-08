// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSCharacter.h"
#include "RTS_Vehicle.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ARTS_Vehicle : public ARTSCharacter
{
	GENERATED_BODY()

	/* billboard component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* GranadeSpawnPoint;
	
public:

	ARTS_Vehicle();

	//~ Begin Unit Interface

	/** called when selected units intended to attack  */
	virtual void Attack_Implementation(FVector AttackLocation) override;

	//~ End Unit Interface

private:

	/** projectile template  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AActor> GranadeTemplateBP;

};
