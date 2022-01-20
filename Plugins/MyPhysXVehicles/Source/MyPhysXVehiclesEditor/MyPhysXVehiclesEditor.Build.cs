// Copyright Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class MyPhysXVehiclesEditor : ModuleRules
	{
        public MyPhysXVehiclesEditor(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
                    "Slate",
                    "SlateCore",
                    "Engine",
                    "UnrealEd",
                    "PropertyEditor",
                    "AnimGraphRuntime",
                    "AnimGraph",
                    "BlueprintGraph",
                    "MyPhysXVehicles",
					"PhysicsCore"
                }
			);

            PrivateDependencyModuleNames.AddRange(
                new string[] 
                {
                    "EditorStyle",
                    "AssetRegistry"
                }
            );
        }
	}
}
