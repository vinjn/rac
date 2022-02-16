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
            string LibRootDirectory = Target.UEThirdPartySourceDirectory;
            string PhysXLibDir = Path.Combine(LibRootDirectory, "PhysX3", "Lib");
            string PhysXSharedDir = Path.Combine(LibRootDirectory, "PhysX3", "PxShared");
            string PhysXIncludeDir = Path.Combine(LibRootDirectory, "PhysX3", "PhysX_3.4", "Include");
            string PhysXSrcDir = Path.Combine(LibRootDirectory, "PhysX3", "PhysX_3.4", "Source");
            Console.WriteLine(PhysXLibDir);
             
            PublicDefinitions.Add("VINJN_UPDATE = 1");
            PublicDefinitions.Add("PX_SUPPORT_PVD = 0");
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


            PublicIncludePaths.AddRange(
                new string[] {
                    // Path.Combine(PhysXIncludeDir, "vehicle"),
                    Path.Combine(PhysXIncludeDir, "cloth"),
                    Path.Combine(PhysXSharedDir, "src/pvd/include"),
                    Path.Combine(PhysXSharedDir, "src/foundation/include"),
                    Path.Combine(PhysXSrcDir, "PhysXExtensions/src/serialization/Xml"),
                    Path.Combine(PhysXSrcDir, "Common/src"),
                    Path.Combine(PhysXSrcDir, "PhysXMetaData/core/include"),
                    Path.Combine(PhysXSrcDir, "PhysXMetaData/extensions/include"),
                    // Path.Combine(PhysXSrcDir, "PhysXVehicle/src/PhysXMetaData/include"),
                    // ... add public include paths required here ...
                }
            );

            PrivateIncludePaths.AddRange(
                new string[] {
                    "MyPhysXVehicles/Private/PhysXVehicle",
                    "MyPhysXVehicles/Private/PhysXVehicle/vehicle",
                    // "MyPhysXVehicles/Private/PhysXVehicle/PhysXMetaData/include",

            //         Path.Combine(PhysXIncludeDir, "vehicle"),
            //         Path.Combine(PhysXSrcDir, "PhysXExtensions/src/serialization/Xml"),
            //         Path.Combine(PhysXSrcDir, "Common/src"),
            //         Path.Combine(PhysXSrcDir, "PhysXVehicle/src/PhysXMetaData/include"),
            //         // ... add public include paths required here ...
                }
            );

            SetupModulePhysicsSupport(Target);

            // string LibrarySuffix = "";
            // string LibDir = Path.Combine(PhysXLibDir, Target.Platform.ToString());
        
            // if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.HoloLens ||
            //     Target.Platform == UnrealTargetPlatform.Win32)
            // {
            //     PublicAdditionalLibraries.Add(Path.Combine(LibDir, "VS" + Target.WindowsPlatform.GetVisualStudioCompilerVersionName(), String.Format("PhysX3Vehicle{0}_{1}.lib", LibrarySuffix, Target.WindowsPlatform.GetArchitectureSubpath())));
            // }
            // else if (Target.Platform == UnrealTargetPlatform.Mac)
            // {
            //     PublicAdditionalLibraries.Add(Path.Combine(LibDir, String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            // }
            // else if (Target.IsInPlatformGroup(UnrealPlatformGroup.Android))
            // {
            //     PublicAdditionalLibraries.Add(Path.Combine(PhysXLibDir, "Android", "ARM64", String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            //     PublicAdditionalLibraries.Add(Path.Combine(PhysXLibDir, "Android", "ARMv7", String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            //     PublicAdditionalLibraries.Add(Path.Combine(PhysXLibDir, "Android", "x64", String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            //     PublicAdditionalLibraries.Add(Path.Combine(PhysXLibDir, "Android", "x86", String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            // }
            // else if (Target.IsInPlatformGroup(UnrealPlatformGroup.Unix))
            // {
            //     PublicAdditionalLibraries.Add(Path.Combine(PhysXLibDir, "Linux", Target.Architecture, String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            // }
            // else if (Target.Platform == UnrealTargetPlatform.IOS)
            // {
            //     PublicAdditionalLibraries.Add(Path.Combine(LibDir, String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            // }
            // else if (Target.Platform == UnrealTargetPlatform.TVOS)
            // {
            //     PublicAdditionalLibraries.Add(Path.Combine(LibDir, String.Format("libPhysX3Vehicle{0}.a", LibrarySuffix)));
            // }
        }
    }
}
