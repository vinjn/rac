// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

 void UMyBlueprintFunctionLibrary::RecreateComponentPhysicsState(UActorComponent* pActorComponent)
 {
     if (pActorComponent != nullptr && pActorComponent->IsValidLowLevel())
     {
         pActorComponent->RecreatePhysicsState();
     }
 }
