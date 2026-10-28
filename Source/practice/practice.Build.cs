// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class practice : ModuleRules
{
	public practice(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PublicIncludePaths.Add(ModuleDirectory + "/Public");
	}
}
