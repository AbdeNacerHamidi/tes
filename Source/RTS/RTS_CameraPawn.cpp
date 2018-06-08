// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_CameraPawn.h"
#include "Components/BillboardComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ARTS_CameraPawn::ARTS_CameraPawn()
{
	/* billboard  */
	ROOT = CreateDefaultSubobject<UBillboardComponent>(TEXT("ROOT"));
	SetRootComponent(ROOT);

	/** camera boom  */
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1500.f;
	CameraBoom->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	/* camera component  */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom);

	/** floating pawn movement component  */
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called to bind functionality to input
void ARTS_CameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/** zoom  */
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARTS_CameraPawn::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARTS_CameraPawn::ZoomOut);

	/** movement  */
	PlayerInputComponent->BindAxis("MoveForward", this, &ARTS_CameraPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARTS_CameraPawn::MoveRight);
}

void ARTS_CameraPawn::MoveForward(float Value)
{
	FloatingPawnMovement->AddInputVector(FVector(Value, 0.f, 0.f));
}

void ARTS_CameraPawn::MoveRight(float Value)
{
	FloatingPawnMovement->AddInputVector(FVector(0.f, Value, 0.f));
}

void ARTS_CameraPawn::ZoomIn()
{
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength + ZoomIncrement, MinZoom, MaxZoom);
}

void ARTS_CameraPawn::ZoomOut()
{
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength - ZoomIncrement, MinZoom, MaxZoom);
}

