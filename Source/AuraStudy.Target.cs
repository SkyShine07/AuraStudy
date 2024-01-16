// copyright  D.H.B

using UnrealBuildTool;
using System.Collections.Generic;

public class AuraStudyTarget : TargetRules
{
	public AuraStudyTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "AuraStudy" } );
	}
}
