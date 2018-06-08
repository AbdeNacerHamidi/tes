// Fill out your copyright notice in the Description page of Project Settings.

#include "Vehicle_AIC.h"
#include "ConstructorHelpers.h"
#include "AI/Navigation/NavFilters/NavigationQueryFilter.h"


AVehicle_AIC::AVehicle_AIC()
{
	/**  set up the default navigation filter class */
	static ConstructorHelpers::FObjectFinder<UBlueprint> NavigationFilterBPClass(TEXT("/Game/TopDownCPP/Blueprints/AI/Navigation/BP_VehicleNavigationQueryFilter"));
	if (NavigationFilterBPClass.Succeeded())
	{
		DefaultNavigationFilterClass = (UClass*)NavigationFilterBPClass.Object->GeneratedClass;
	}

	/**  BP_VehicleNavigationQueryFilter must exclude all navigation areas 
	*	 that you want to prevent moving through. In our case:
	*	 NavArea_Null and BP_NavArea_NoVehicle(derived from Nav Area class and simple set the color),
	*	 BP_NavArea_NoVehicle must be set as AreaClass in Nav Modifier Volume that located in places 
	*	 AVehicle_AIC NOT intended to move its pawn.
	*/

	
}
