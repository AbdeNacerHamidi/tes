// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Vehicle.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "AI/Vehicle_AIC.h"
#include "Components/BillboardComponent.h"
#include "ConstructorHelpers.h"

ARTS_Vehicle::ARTS_Vehicle()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.f);
	GetCapsuleComponent()->SetCapsuleRadius(96.f);

	/** different AI controller for different navigation movement  */
	AIControllerClass = AVehicle_AIC::StaticClass();

	GetCursorToWorld()->SetWorldScale3D(FVector(1.f, 3.f, 3.f));

	/* billboard  */
	GranadeSpawnPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));
	GranadeSpawnPoint->SetupAttachment(RootComponent);
	GranadeSpawnPoint->SetRelativeLocation(FVector(0.f, 0.f, 150.f));

	/**  set the  class */
	static ConstructorHelpers::FClassFinder<AActor> BPClass(TEXT("/Game/TopDownCPP/Blueprints/BP_Granade"));
	if (BPClass.Class)
	{
		GranadeTemplateBP = BPClass.Class;
	}
}

void ARTS_Vehicle::Attack_Implementation(FVector AttackLocation)
{
	if (GranadeTemplateBP)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator; //  GetController();
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			FVector SpawnLocation = GranadeSpawnPoint->GetComponentLocation();
			FRotator SpawnRotation = (AttackLocation - SpawnLocation).Rotation();
			
			AActor* Spawned = World->SpawnActor<AActor>(GranadeTemplateBP, SpawnLocation, SpawnRotation, SpawnParams);
			if (Spawned)
			{
			
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GranadeTemplateBP == NULL"));
	}
}
