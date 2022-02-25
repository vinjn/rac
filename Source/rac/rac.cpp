// Fill out your copyright notice in the Description page of Project Settings.

#include "rac.h"
#include "Modules/ModuleManager.h"
#include "Misc/DefaultValueHelper.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MyWheeledVehicle.h"

#if PLATFORM_WINDOWS || PLATFORM_ANDROID
#include "renderdoc_app.h"
#endif

#if PLATFORM_ANDROID
#include <dlfcn.h>
#endif

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
				vehicle->DebugMode = Mode_Count - 1;
		}
#if PLATFORM_WINDOWS || PLATFORM_ANDROID
		else if (ArgNoWhitespaces.Equals("rdc"))
		{
			static RENDERDOC_API_1_5_0* rdoc_api = NULL;
			// Dynamically link renderdoc library and get the api handle
			UE_LOG(LogTemp, Warning, TEXT("Trigger renderdoc capture"));

			if (rdoc_api == NULL)
            {
#if 0 && PLATFORM_WINDOWS
                if (HMODULE mod = GetModuleHandleA("renderdoc.dll"))
                {
                    pRENDERDOC_GetAPI RENDERDOC_GETAPI = (pRENDERDOC_GetAPI)GetProcAddressA(mod, "RENDERDOC_GetAPI");
                    int ret = RENDERDOC_GETAPI(eRENDERDOC_API_Version_1_5_0, (void**)&rdoc_api);
                }
#elif PLATFORM_ANDROID
                if (void* mod = dlopen("libVkLayer_GLES_RenderDoc.so", RTLD_NOW | RTLD_NOLOAD))
                {
                    pRENDERDOC_GetAPI RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)dlsym(mod, "RENDERDOC_GetAPI");
                    int ret = RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_5_0, (void**)&rdoc_api);
                }
#endif
			}

			if (rdoc_api != NULL)
			{
				rdoc_api->TriggerCapture();
				uint32_t NumCaptrues = rdoc_api->GetNumCaptures();
				if (NumCaptrues > 0)
				{
					uint32_t pathlength = 0;
					uint32_t idx = NumCaptrues - 1;
					rdoc_api->GetCapture(idx, NULL, &pathlength, NULL);
					if (pathlength > 0)
					{
						char* filename = new char[pathlength+1];
						rdoc_api->GetCapture(idx, filename, NULL, NULL);
						FString str(filename);
						UE_LOG(LogTemp, Warning, TEXT("[%d]: %s"), idx, *str);

						delete[] filename;
					}
				}
			}
		}
#endif

		return true;
	}
}
GMExec;
