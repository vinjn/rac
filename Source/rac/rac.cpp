// Fill out your copyright notice in the Description page of Project Settings.

#include "rac.h"
#include "Modules/ModuleManager.h"
#include "Misc/DefaultValueHelper.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MyWheeledVehicle.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, rac, "rac" );

/** Exec used to execute GM commands on the game thread. */
static class FGMCmdExec : private FSelfRegisteringExec
{
public:
	/** Console commands, see embeded usage statement **/
	virtual bool Exec(UWorld* world, const TCHAR* Cmd, FOutputDevice& Ar) override
	{
		const bool bGmCommand = FParse::Command(&Cmd, TEXT("gm"));
		if (!bGmCommand) return false;

		FString AddArgs;
		const TCHAR* TempCmd = Cmd;

		FString ArgNoWhitespaces = FDefaultValueHelper::RemoveWhitespaces(TempCmd);
		const bool bIsEmpty = ArgNoWhitespaces.IsEmpty();
		if (bIsEmpty) return true;

		APawn* pawn = UGameplayStatics::GetPlayerPawn(world, 0);
		AMyWheeledVehicle* vehicle = (AMyWheeledVehicle*)pawn;
		if (ArgNoWhitespaces.Equals("right"))
		{
			vehicle->DebugMode++;
			if (vehicle->DebugMode >= Mode_Count)
				vehicle->DebugMode = Mode_None;
		}
		else if (ArgNoWhitespaces.Equals("left"))
		{
			vehicle->DebugMode--;
			if (vehicle->DebugMode < Mode_None)
				vehicle->DebugMode = Mode_DrawDebugLine;
		}

		return true;
	}
}
GMExec;
