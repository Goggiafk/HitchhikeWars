// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HitchhikeWars : ModuleRules
{
	public HitchhikeWars(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
