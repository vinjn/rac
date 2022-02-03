// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RAC_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Physics")
	static void RecreateComponentPhysicsState(class UActorComponent* pActorComponent);

	UFUNCTION(BlueprintCallable, Category = "Physics")
	static float GetVehicleWheelShapeRadius(class UMyVehicleWheel* wheel);

	UFUNCTION(BlueprintCallable, Category = "Physics")
	static void SetVehicleWheelShapeRadius(class UMyVehicleWheel* wheel, float radius);

	UFUNCTION(BlueprintCallable, Category = "Physics")
	static float GetVehicleWheelShapeWidth(class UMyVehicleWheel* wheel);

	UFUNCTION(BlueprintCallable, Category = "Physics")
	static void SetVehicleWheelShapeWidth(class UMyVehicleWheel* wheel, float width);

};
