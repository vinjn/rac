// Copyright Epic Games, Inc. All Rights Reserved.



#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/DataAsset.h"
#include "MyTireConfig.generated.h"

class UPhysicalMaterial;

/** Allows overriding of friction of this tire config on a specific material */
USTRUCT()
struct FMyTireConfigMaterialFriction
{
	GENERATED_USTRUCT_BODY()

	/** Physical material for friction scale */
	UPROPERTY(EditAnywhere, Category = FMyTireConfigMaterialFriction)
	UPhysicalMaterial*		PhysicalMaterial;

	/** Friction scale for this type of material */
	UPROPERTY(EditAnywhere, Category = FMyTireConfigMaterialFriction)
	float					FrictionScale;

	FMyTireConfigMaterialFriction()
		: PhysicalMaterial(nullptr)
		, FrictionScale(1.0f)
	{
	}
};

/** Represents a type of tire surface used to specify friction values against physical materials. */
class UE_DEPRECATED(4.26, "PhysX is deprecated. Use the Chaos physics and the ChaosVehiclePhysics Plugin.") UMyTireConfig;
UCLASS()
class  UMyTireConfig : public UDataAsset
{
	GENERATED_BODY()

private:

	// Scale the tire friction for this tire type
	UPROPERTY(EditAnywhere, Category = TireConfig)
	float								FrictionScale;

	/** Tire friction scales for specific physical materials. */
	UPROPERTY(EditAnywhere, Category = TireConfig)
	TArray<FMyTireConfigMaterialFriction> TireFrictionScales;

private:

	// Tire config ID to pass to PhysX
	uint32								TireConfigID;

public:

	UMyTireConfig();

	// All loaded tire types - used to assign each tire type a unique TireConfigID
	static TArray<TWeakObjectPtr<UMyTireConfig>>			AllTireConfigs;

	/**
	* Getter for FrictionScale
	*/
	float GetFrictionScale() { return FrictionScale; }

	/**
	* Setter for FrictionScale
	*/
	void SetFrictionScale(float NewFrictionScale);

	/** Set friction scaling for a particular material */
	void SetPerMaterialFrictionScale(UPhysicalMaterial*	PhysicalMaterial, float	NewFrictionScale);

	/**
	* Getter for TireConfigID
	*/
	int32 GetTireConfigID() { return TireConfigID; }

	/**
	* Called after the C++ constructor and after the properties have been initialized, but before the config has been loaded, etc.
	* mainly this is to emulate some behavior of when the constructor was called after the properties were initialized.
	*/
	virtual void PostInitProperties() override;

	/**
	* Called before destroying the object.  This is called immediately upon deciding to destroy the object, to allow the object to begin an
	* asynchronous cleanup process.
	*/
	virtual void BeginDestroy() override;

	/** Get the friction for this tire config on a particular physical material */
	float GetTireFriction(UPhysicalMaterial* PhysicalMaterial);

#if WITH_EDITOR

	/**
	* Respond to a property change in editor
	*/
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

#endif //WITH_EDITOR

protected:

	/**
	* Add this tire type to the TireConfigs array
	*/
	void NotifyTireFrictionUpdated();


};
