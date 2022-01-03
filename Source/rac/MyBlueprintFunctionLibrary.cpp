// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "VehicleWheel.h"

 void UMyBlueprintFunctionLibrary::RecreateComponentPhysicsState(UActorComponent* pActorComponent)
 {
     if (pActorComponent != nullptr && pActorComponent->IsValidLowLevel())
     {
         pActorComponent->RecreatePhysicsState();
     }
 }

float UMyBlueprintFunctionLibrary::GetVehicleWheelShapeRadius(UVehicleWheel* wheel)
{
    return wheel->ShapeRadius;
}

void UMyBlueprintFunctionLibrary::SetVehicleWheelShapeRadius(UVehicleWheel* wheel, float radius)
{
    wheel->ShapeRadius = radius;
}

float UMyBlueprintFunctionLibrary::GetVehicleWheelShapeWidth(UVehicleWheel* wheel)
{
    return wheel->ShapeWidth;
}

void UMyBlueprintFunctionLibrary::SetVehicleWheelShapeWidth(UVehicleWheel* wheel, float width)
{
    wheel->ShapeWidth = width;
}
