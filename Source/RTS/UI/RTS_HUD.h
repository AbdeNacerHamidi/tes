// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RTS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API URTS_HUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/** called to reset attack check box to unchecked state */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void ResetAttack();

	/** called to set owning player PC reference  */
	void SetPC(class ARTSPlayerController* NewPC) { PC = NewPC; }

	/** called to play HUD animations */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void PlayAnim();

private:
	
	/**  owning player PC reference  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class ARTSPlayerController* PC;

};
