// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class HitchhikeWars : ModuleRules
{
	public HitchhikeWars(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AssetRegistry", "OnlineSubsystem", "OnlineSubsystemSteam", "UMG" });
		
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "steam", "lib", "steam_api64.lib"));
	}
}
