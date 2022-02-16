// Fill out your copyright notice in the Description page of Project Settings.

#include "rac.h"
#include "Modules/ModuleManager.h"
#include "Misc/DefaultValueHelper.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, rac, "rac" );

/** Exec used to execute GM commands on the game thread. */
static class FGMCmdExec : private FSelfRegisteringExec
{
public:
	/** Console commands, see embeded usage statement **/
	virtual bool Exec(UWorld*, const TCHAR* Cmd, FOutputDevice& Ar) override
	{
		const bool bGmCommand = FParse::Command(&Cmd, TEXT("gm"));
		if (!bGmCommand) return false;

		FString AddArgs;
		const TCHAR* TempCmd = Cmd;

		FString ArgNoWhitespaces = FDefaultValueHelper::RemoveWhitespaces(TempCmd);
		const bool bIsEmpty = ArgNoWhitespaces.IsEmpty();
		if (bIsEmpty) return true;

		return true;
	}
}
GMExec;
