// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using UnrealBuildTool;
using System.IO;

public class ZMQControl : ModuleRules
{
	public ZMQControl(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"GameplayTags",
				"Json"
			});
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Projects"
			});
		
		string externalLib = Path.Combine(ModuleDirectory, "ThirdParty", "Library");
		string externalSource = Path.Combine(ModuleDirectory, "ThirdParty", "Include");

		PublicIncludePaths.Add(externalSource);

        PublicDefinitions.Add("ZMQ_STATIC");
		
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(externalLib, "ZMQ", "Win64", "libzmq-v141-mt-s-4_3_2.lib"));
			
            AddRuntimeDependencies(
	            new string[]
	            {
	                "libzmq-v141-mt-s-4_3_2.lib"
				},
				Path.Combine(externalLib, "ZMQ", "Win64"),
	            false
	        );
		}
	}
	
	void AddRuntimeDependencies(string[] DllNames, string LibraryPath, bool DelayLoad)
	{
		string binariesDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "Binaries", "Win64"));
		string engineBinaries = Path.GetFullPath(Path.Combine(EngineDirectory, "Binaries", "Win64"));
		
		foreach (string iter in DllNames)
		{
			string dllPath = Path.Combine(LibraryPath, iter);
			string destDllPath = Path.Combine(binariesDir, iter);
			string engineDllPath = Path.Combine(engineBinaries, iter);
			
			if (!File.Exists(destDllPath) && File.Exists(dllPath))
			{
				File.Copy(dllPath, destDllPath, false);
			}
			if (!File.Exists(engineDllPath) && File.Exists(dllPath))
			{
				File.Copy(dllPath, engineDllPath, false);
			}
			
			RuntimeDependencies.Add(destDllPath);
			RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)", iter), destDllPath);

			if (DelayLoad)
			{
				PublicDelayLoadDLLs.Add(iter);
			}
		}
	}
}
