// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RDiVehicleBPLibrary.h"
#include "RDiVehicle.h"
#include "MyWheeledVehicleMovementComponent.h"
#include "MyVehicleWheel.h"
#include "PhysXPublic.h"
#include "Physics/PhysicsFiltering.h"
#include "Math/UnrealMathUtility.h"
#include "Engine.h"

URDiVehicleBPLibrary::URDiVehicleBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float URDiVehicleBPLibrary::RDiVehicleSampleFunction(float Param)
{
	return -1;
}

void URDiVehicleBPLibrary::TouchProcessing(FVector touchPos, FVector touchBegin, float &th, float &steer)
{
	FVector2D size = FVector2D( 1, 1 );
	
	if ( GEngine && GEngine->GameViewport )
	{
		GEngine->GameViewport->GetViewportSize( /*out*/size );
	}

	// если правая половина, то это газ
	float xn = touchPos.X / size.X;
	float yn = touchPos.Y / size.Y;
	float t = 0;


	if(xn > 0.5) {
		t = (touchPos.Y - touchBegin.Y)*-0.01;
		if((t >= 0) && (t < 0.5)) th = 0.6;
		else if(t > 0.5) th = 1.0f;
		else if((t < -0.2) && (t > -0.5)) th = -0.4;
		else if(t<-0.5) th = -1.0f;

		th = FMath::Clamp(th, -1.0f, 1.0f);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Screen size: %fx%f"), Result.X, Result.Y );
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Size X = %f , Size Y = %f"), Result.X, Result.Y));
}

void URDiVehicleBPLibrary::TouchBegin(FVector touchPos, FVector &touchBegin, float &th, float &steer)
{
	th = 0.6;
	touchBegin = touchPos;
}

void URDiVehicleBPLibrary::TouchEnd(float &th, float &steer)
{
	th = 0.0;
}

void URDiVehicleBPLibrary::throttleBrakeManager(float inputThrottle, float inputOvd, int gearIn, float rpm, float fwdSpeed, TArray<float> speedGear, TArray<float> speedGearOvd, bool noThrottleNeutral, float &throttle, float &brake, int &gearOut)
{
    fwdSpeed *= 0.036f;
    // раннее сцепление
    float clutchThreshold = 1200;
    // позднее сцепление на полном газу
    if(inputOvd > 0.0f) {
        clutchThreshold = 3200;
    }
    //UE_LOG(LogTemp, Warning, TEXT("Gear = 0") );
    // выбор передачи
    int targetGear = speedGear.Num() + 1;
    for (int i = 0; i < speedGear.Num(); i++)
    {
        int tgtGear = (int)speedGear[i];
        if(inputOvd > 0.0f) tgtGear = (int)speedGearOvd[i];

        if( ((int)fwdSpeed / tgtGear) < 1) {
            targetGear = i+1;
            break;
        }
    }
    /*
    int targetGear = 1 + (int)fwdSpeed / 30;
    if(fabs(inputOvd)>0) {
        targetGear = 1 + (int)fwdSpeed / 40;
    }
    */
    gearOut = gearIn;
    int thNeutral = targetGear;
    
    if(noThrottleNeutral) thNeutral = 0;

    // желаем ехать вперед
    if( inputThrottle > 0 ) {
        // если движемся вперед или стоим на месте (немножко катимся назад) или шлифуем
        if(fwdSpeed >= -500.0f) {
            throttle = inputThrottle + inputOvd;
            // передачу втыкаем после границы
            if(rpm > clutchThreshold) {
                gearOut = targetGear;
                //UE_LOG(LogTemp, Warning, TEXT("Gear = gearout, gearout: %i"), targetGear );
            }
            /*
            else if(rpm < clutchThreshold - 1000) {
                gearOut = thNeutral;
                //UE_LOG(LogTemp, Warning, TEXT("Gear = 0") );
            }
            */
            brake = 0;
        }
        // если движемся назад то тормозим
        else {
            throttle = 0;
            gearOut = 0;
            brake = 1;
            //UE_LOG(LogTemp, Warning, TEXT("Else Gear = 0") );
        }
    }
    // желаем ехать назад
    else if(inputThrottle < 0) {
        // если стоим на месте или немножко катимся вперед
        if(fwdSpeed <= 5.0f) {
            throttle = inputThrottle - inputOvd;
            if(rpm > clutchThreshold) gearOut = -1;
            //else if(rpm < clutchThreshold - 500) gearOut = 0;
            brake = 0;
        }
        // если движемся вперед то тормозим
        else {
            throttle = 0;
            gearOut = 0;
            brake = -1;
        }
    }
    // если газ брошен
    else{
        // если скорость больше 10 кмч то передачу не вытыкаем
         if(abs(fwdSpeed) > 10.0f){
            if(noThrottleNeutral) {
                gearOut = 0;
            }
            else {
                gearOut = thNeutral;
            }
        }
        // если меньше включить нейтралку
        else {
            gearOut = 0;
        }
    }

    //UE_LOG(LogTemp, Warning, TEXT("Th IN: %f, Th OUT: %f, gearOut: %i, brake: %f, spd: %f"), inputThrottle, throttle, gearOut, brake, fwdSpeed );

}

FString URDiVehicleBPLibrary::getGearString( int gearIn )
{
    if( gearIn < 0 ) return "R";
    else if( gearIn == 0) return "N";
    else return FString::FromInt(gearIn);
}

bool URDiVehicleBPLibrary::GetWheelSlip(UMyWheeledVehicleMovementComponent* pVehicle, int whNum, float Threshold, float &value)
{
	//bool SlipThresholdExceeded = pVehicle->CheckSlipThreshold(longitudal, lateral);
	// если колесо в воздухе то сразу нет
	if(pVehicle->Wheels[whNum]->IsInAir()) return false;

	value = fabs(pVehicle->Wheels[whNum]->DebugLatSlip) + fabs(pVehicle->Wheels[whNum]->DebugLongSlip);
	if(value > Threshold) return true;
	else return false;
}


