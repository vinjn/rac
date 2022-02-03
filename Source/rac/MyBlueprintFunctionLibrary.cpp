// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "MyVehicleWheel.h"

 void UMyBlueprintFunctionLibrary::RecreateComponentPhysicsState(UActorComponent* pActorComponent)
 {
     if (pActorComponent != nullptr && pActorComponent->IsValidLowLevel())
     {
         pActorComponent->RecreatePhysicsState();
     }
 }

float UMyBlueprintFunctionLibrary::GetVehicleWheelShapeRadius(UMyVehicleWheel* wheel)
{
    return wheel->ShapeRadius;
}

void UMyBlueprintFunctionLibrary::SetVehicleWheelShapeRadius(UMyVehicleWheel* wheel, float radius)
{
    wheel->ShapeRadius = radius;
}

float UMyBlueprintFunctionLibrary::GetVehicleWheelShapeWidth(UMyVehicleWheel* wheel)
{
    return wheel->ShapeWidth;
}

void UMyBlueprintFunctionLibrary::SetVehicleWheelShapeWidth(UMyVehicleWheel* wheel, float width)
{
    wheel->ShapeWidth = width;
}
