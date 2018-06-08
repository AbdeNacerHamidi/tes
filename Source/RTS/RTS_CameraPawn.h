// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTS_CameraPawn.generated.h"

UCLASS()
class RTS_API ARTS_CameraPawn : public APawn
{
	GENERATED_BODY()

	/* billboard component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* ROOT;
	
	/** camera boom  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	/* camera component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
	
	/** floating pawn movement component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* FloatingPawnMovement;

public:

	// Sets default values for this pawn's properties
	ARTS_CameraPawn();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	/** movement  */
	void MoveForward(float Value);
	void MoveRight(float Value);

	/** zoom  */
	void ZoomIn();
	void ZoomOut();

	// -----------------------------------------------------------------------------------

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float MaxZoom = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float MinZoom = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float ZoomIncrement = 100.f;
	
};
