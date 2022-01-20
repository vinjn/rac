// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyTireConfig.h"
#include "EngineDefines.h"
#include "PhysXPublic.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#if WITH_PHYSX
#include "MyPhysXVehicleManager.h"
#endif

PRAGMA_DISABLE_DEPRECATION_WARNINGS

TArray<TWeakObjectPtr<UMyTireConfig>> UMyTireConfig::AllTireConfigs;

UMyTireConfig::UMyTireConfig()
{
	// Property initialization
	FrictionScale = 1.0f;
}

void UMyTireConfig::SetFrictionScale(float NewFrictionScale)
{
	if (NewFrictionScale != FrictionScale)
	{
		FrictionScale = NewFrictionScale;

		NotifyTireFrictionUpdated();
	}
}

void UMyTireConfig::SetPerMaterialFrictionScale(UPhysicalMaterial* PhysicalMaterial, float NewFrictionScale)
{
	// See if we already have an entry for this material
	bool bFoundEntry = false;
	for (FMyTireConfigMaterialFriction MatFriction : TireFrictionScales)
	{
		if (MatFriction.PhysicalMaterial == PhysicalMaterial)
		{
			// We do, update it
			MatFriction.FrictionScale = NewFrictionScale;
			bFoundEntry = true;
			break;
		}
	}

	// We don't have an entry, add one
	if (!bFoundEntry)
	{
		FMyTireConfigMaterialFriction MatFriction;
		MatFriction.PhysicalMaterial = PhysicalMaterial;
		MatFriction.FrictionScale = NewFrictionScale;
		TireFrictionScales.Add(MatFriction);
	}

	// Update friction table
	NotifyTireFrictionUpdated();
}


void UMyTireConfig::PostInitProperties()
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		// Set our TireConfigID - either by finding an available slot or creating a new one
		int32 TireConfigIndex = AllTireConfigs.Find(NULL);

		if (TireConfigIndex == INDEX_NONE)
		{
			TireConfigIndex = AllTireConfigs.Add(this);
		}
		else
		{
			AllTireConfigs[TireConfigIndex] = this;
		}

		TireConfigID = (int32)TireConfigIndex;

		NotifyTireFrictionUpdated();
	}

	Super::PostInitProperties();
}

void UMyTireConfig::BeginDestroy()
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		// free our TireTypeID
		check(AllTireConfigs.IsValidIndex(TireConfigID));
		check(AllTireConfigs[TireConfigID] == this);
		AllTireConfigs[TireConfigID] = NULL;

		NotifyTireFrictionUpdated();
	}

	Super::BeginDestroy();
}

void UMyTireConfig::NotifyTireFrictionUpdated()
{
#if WITH_PHYSX_VEHICLES
	FMyPhysXVehicleManager::UpdateTireFrictionTable();
#endif // WITH_PHYSX
}

#if WITH_EDITOR
void UMyTireConfig::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	NotifyTireFrictionUpdated();
}
#endif //WITH_EDITOR

float UMyTireConfig::GetTireFriction(UPhysicalMaterial* PhysicalMaterial)
{
	// Get friction from tire config
	float Friction = (PhysicalMaterial != nullptr) ? PhysicalMaterial->Friction : 1.f;

	// Scale by tire config scale
	Friction *= FrictionScale;

	// See if we have a material-specific scale as well
	for (FMyTireConfigMaterialFriction MatFriction : TireFrictionScales)
	{
		if (MatFriction.PhysicalMaterial == PhysicalMaterial)
		{
			Friction *= MatFriction.FrictionScale;
			break;
		}
	}

	return Friction;
}


PRAGMA_ENABLE_DEPRECATION_WARNINGS
