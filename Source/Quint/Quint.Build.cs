// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Quint : ModuleRules
{
	public Quint(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});
        PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Http", "Json", "JsonUtilities" });
    }
}
