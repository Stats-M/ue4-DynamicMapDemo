// DynamicMap Demo. Copyright (C) 2022 Stanislav Moskalev

using UnrealBuildTool;
using System.Collections.Generic;

public class DynamicMapDemoEditorTarget : TargetRules
{
	public DynamicMapDemoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DynamicMapDemo" } );
	}
}
