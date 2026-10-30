using UnrealBuildTool;

public class practice : ModuleRules
{
    public practice(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG"
        });
        PublicIncludePaths.Add(ModuleDirectory + "/Public");
    }
}
