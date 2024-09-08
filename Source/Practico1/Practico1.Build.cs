// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Practico1 : ModuleRules
{
	public Practico1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
