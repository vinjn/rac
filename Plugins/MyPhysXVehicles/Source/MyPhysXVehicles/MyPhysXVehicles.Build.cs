// Copyright Epic Games, Inc. All Rights Reserved.

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

            // string LibRootDirectory = Target.UEThirdPartySourceDirectory;
            // string PhysXLibDir = Path.Combine(LibRootDirectory, "PhysX3", "Lib");
            // string LibrarySuffix = LibraryMode.AsSuffix();
    
            // PublicAdditionalLibraries.Add(Path.Combine(LibDir, "VS" + Target.WindowsPlatform.GetVisualStudioCompilerVersionName(), 
            //     String.Format("PhysX3Vehicle{0}_{1}.lib", LibrarySuffix, Target.WindowsPlatform.GetArchitectureSubpath())));

            PublicAdditionalLibraries.Add("d:/Epic Games/UE_4.27/Engine/Source/ThirdParty/PhysX3/Lib/Win64/VS2015/PhysX3Vehicle_x64.lib");
        }
    }
}
