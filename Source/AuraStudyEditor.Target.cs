// copyright  D.H.B

using UnrealBuildTool;
using System.Collections.Generic;

public class AuraStudyEditorTarget : TargetRules
{
	public AuraStudyEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "AuraStudy" } );
	}
}
