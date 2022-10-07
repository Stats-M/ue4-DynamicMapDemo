// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

using UnrealBuildTool;

public class DynamicMapDemo : ModuleRules
{
	public DynamicMapDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"ProceduralMeshComponent", 
			"UnrealEd" 
		});

		// -For use of ProceduralMesh we must add "ProceduralMeshComponent" here.
		// Also add paths to ProceduralMeshComponent.h and ProceduralMeshComponent.generated.h
		// to VC project properties, both to Include paths and IntelliSence paths
		// -"UnrealEd" is required here for use AutomationEditorCommon.h (UE tests automation)
		PrivateDependencyModuleNames.AddRange(new string[] { 
			"ProceduralMeshComponent", 
			"UnrealEd" 
		});

		// Sometimes subfolders with .h files are not referenced correctly
		// This way we can setup additional lookup directories
		PublicIncludePaths.AddRange(new string[] { 
			"DynamicMapDemo/Public/Camera",
			"DynamicMapDemo/Public/UI",
			"DynamicMapDemo/Public/Mapper",
			"DynamicMapDemo/Public/Misc",
			"DynamicMapDemo/Public/Subsystems"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
