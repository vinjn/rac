// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RDiVehicleBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class URDiVehicleBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "RDiVehicle sample test testing"), Category = "RDiVehicle")
	static float RDiVehicleSampleFunction(float Param);

	// Mobile Touch Interface
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TouchProcessing", Keywords = "RDiVehicle touch"), Category="RDiVehicle Touch")
	static void TouchProcessing(FVector touchPos, FVector touchBegin, float &th, float &steer);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TouchBegin", Keywords = "RDiVehicle touch"), Category="RDiVehicle Touch")
	static void TouchBegin(FVector touchPos, FVector &touchBegin, float &th, float &steer);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TouchEnd", Keywords = "RDiVehicle touch"), Category="RDiVehicle Touch")
	static void TouchEnd(float &th, float &steer);

	// Our implementation of automatic gearbox (very simple and primitive)
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GearBox", Keywords = "RDiVehicle gearbox"), Category="RDiVehicle")
	static void throttleBrakeManager(float inputThrottle, float inputOvd, int gearIn, float rpm, float fwdSpeed, TArray<float> speedGear, TArray<float> speedGearOvd, bool noThrottleNeutral, float &throttle, float &brake, int &gearOut);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "getGearString", Keywords = "RDiVehicle gearbox"), Category="RDiVehicle")
	static FString getGearString( int gearIn );

	// Get wheel slip from PhysX
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetWheelSlip", Keywords = "RDiVehicle wheel"), Category="RDiVehicle")
	static bool GetWheelSlip(UWheeledVehicleMovementComponent* pVehicle, int whNum, float Threshold, float &value);
	
};
