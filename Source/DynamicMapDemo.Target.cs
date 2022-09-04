// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

using UnrealBuildTool;
using System.Collections.Generic;

public class DynamicMapDemoTarget : TargetRules
{
	public DynamicMapDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DynamicMapDemo" } );
	}
}
