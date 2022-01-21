// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;
using System;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class MyPhysXVehicles : ModuleRules
	{
        public MyPhysXVehicles(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
                    "Engine",
                    "EngineSettings",
                    "RenderCore",
                    "AnimGraphRuntime",
                    "RHI",
                    "PhysX"
				}
				);

            SetupModulePhysicsSupport(Target);

            string LibRootDirectory = Target.UEThirdPartySourceDirectory;
            string PhysXLibDir = Path.Combine(LibRootDirectory, "PhysX3", "Lib");
            Console.WriteLine(PhysXLibDir);
            string LibrarySuffix = "";
            string LibDir = Path.Combine(PhysXLibDir, Target.Platform.ToString());
        
            if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.HoloLens ||
                Target.Platform == UnrealTargetPlatform.Win32)
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibDir, "VS" + Target.WindowsPlatform.GetVisualStudioCompilerVersionName(), String.Format("PhysX3Vehicle{0}_{1}.lib", LibrarySuffix, Target.WindowsPlatform.GetArchitectureSubpath())));
            }
            else if (Target.Platform == UnrealTargetPlatform.Mac)
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibDir, String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            }
            else if (Target.IsInPlatformGroup(UnrealPlatformGroup.Android))
            {
                PublicAdditionalLibraries.Add(Path.Combine(PhysXLibDir, "Android", "ARM64", String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
                PublicAdditionalLibraries.Add(Path.Combine(PhysXLibDir, "Android", "ARMv7", String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
                PublicAdditionalLibraries.Add(Path.Combine(PhysXLibDir, "Android", "x64", String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
                PublicAdditionalLibraries.Add(Path.Combine(PhysXLibDir, "Android", "x86", String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            }
            else if (Target.IsInPlatformGroup(UnrealPlatformGroup.Unix))
            {
                PublicAdditionalLibraries.Add(Path.Combine(PhysXLibDir, "Linux", Target.Architecture, String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            }
            else if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibDir, String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            }
            else if (Target.Platform == UnrealTargetPlatform.TVOS)
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibDir, String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            }

            // PublicAdditionalLibraries.Add("C:/UE_4.27/Engine/Source/ThirdParty/PhysX3/Lib/Win64/VS2015/PhysX3Vehicle_x64.lib");
            // PublicAdditionalLibraries.Add("d:/UE_4.27/Engine/Source/ThirdParty/PhysX3/Lib/Win64/VS2015/PhysX3Vehicle_x64.lib");
            // PublicAdditionalLibraries.Add("d:/Epic Games/UE_4.27/Engine/Source/ThirdParty/PhysX3/Lib/Win64/VS2015/PhysX3Vehicle_x64.lib");
        }
    }
}
