// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPhysXVehiclesEditorPlugin.h"
#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "MyWheeledVehicleMovementComponent4WDetails.h"
#include "PropertyEditorModule.h"
#include "MyVehicleTransmissionDataCustomization.h"
#include "Modules/ModuleManager.h"
#include "AssetData.h"
#include "AssetRegistryModule.h"
#include "Vehicles/TireType.h"
#include "MyTireConfig.h"
#include "MyVehicleWheel.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "HAL/IConsoleManager.h"
#include "Engine/Blueprint.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class FPhysXVehiclesEditorPlugin : public IPhysXVehiclesEditorPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomClassLayout("WheeledVehicleMovementComponent4W", FOnGetDetailCustomizationInstance::CreateStatic(&FWheeledVehicleMovementComponent4WDetails::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("VehicleTransmissionData", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyVehicleTransmissionDataCustomization::MakeInstance));
		PropertyModule.NotifyCustomizationModuleChanged();
	}


	virtual void ShutdownModule() override
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout("WheeledVehicleMovementComponent4W");
		PropertyModule.UnregisterCustomPropertyTypeLayout("VehicleTransmissionData");
		PropertyModule.NotifyCustomizationModuleChanged();
	}
};

IMPLEMENT_MODULE(FPhysXVehiclesEditorPlugin, PhysXVehiclesEditor)

PRAGMA_ENABLE_DEPRECATION_WARNINGS


// CONVERT TIRE TYPES UTIL
static const FString EngineDir = TEXT("/Engine/");
