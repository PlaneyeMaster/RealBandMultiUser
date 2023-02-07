// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class BackUp : ModuleRules
{
	public BackUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				Path.Combine(EngineDirectory, @"Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Public"),
                Path.Combine(EngineDirectory, @"Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public")
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				Path.Combine(EngineDirectory, @"Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Public")
            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
                "EditorSubsystem",
                "Engine",
                "Blutility",
				"Concert",
                "ConcertSyncClient",
                "ConcertTransport",
                "MultiUserClient",
                "EditorWidgets",
                "PropertyEditor"
				
				// ... add other public dependencies that you statically link with here ...
			}
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"EditorFramework",
				"UnrealEd",
				"ToolMenus",
                "Concert",
				"ConcertSyncClient",
                "ConcertTransport",
                "EditorWidgets",
                "MultiUserClient",
                "CoreUObject",
				"Engine",
                "PropertyEditor",
                "EditorFramework",
                "Slate",
				"SlateCore",
                "Json",
                "UnrealEd",
                "HTTP"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
