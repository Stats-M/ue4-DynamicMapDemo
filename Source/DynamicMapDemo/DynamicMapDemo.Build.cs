// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

using UnrealBuildTool;

public class DynamicMapDemo : ModuleRules
{
	public DynamicMapDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Sometimes subfolders with .h files are not referenced correctly
		// This way we can setup additional lookup directories
		PublicIncludePaths.AddRange(new string[] { 
			"DynamicMapDemo/Public/Camera",
			"DynamicMapDemo/Public/UI",
			"DynamicMapDemo/Public/Mapper"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
