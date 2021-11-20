// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CapstonePrototype1 : ModuleRules
{
	public CapstonePrototype1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
