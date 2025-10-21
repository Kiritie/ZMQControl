// Fill out your copyright notice in the Description page of Project Settings.

#include "ZMQControlStatics.h"

#include "ZMQControlTypes.h"
#include "Interfaces/IPluginManager.h"

TArray<FZMQConnectInfo> UZMQControlStatics::GetZMQConnectInfos()
{
	TArray<FZMQConnectInfo> ConfigList;

	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("ZMQControl"));
	if (!Plugin.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Plugin not found."));
		return ConfigList;
	}

	FString ConfigDir = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Config"));
	FString ConfigPath = FPaths::Combine(ConfigDir, TEXT("ConnectConfig.txt"));

	FString FileContent;
	if (!FFileHelper::LoadFileToString(FileContent, *ConfigPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load config file: %s"), *ConfigPath);
		return ConfigList;
	}

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContent);
	TArray<TSharedPtr<FJsonValue>> JsonArray;

	if (!FJsonSerializer::Deserialize(Reader, JsonArray) || JsonArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON from: %s"), *ConfigPath);
		return ConfigList;
	}

	for (TSharedPtr<FJsonValue> Value : JsonArray)
	{
		if (!Value.IsValid() || !Value->AsObject().IsValid())
			continue;

		TSharedPtr<FJsonObject> Obj = Value->AsObject();
		FZMQConnectInfo Item;

		Obj->TryGetStringField(TEXT("name"), Item.Name);
		Obj->TryGetNumberField(TEXT("channel_type"), Item.ChannelType);
		Obj->TryGetStringField(TEXT("server_url"), Item.ServerURL);

		ConfigList.Add(Item);
	}

	UE_LOG(LogTemp, Log, TEXT("Loaded %d connection entries from %s"), ConfigList.Num(), *ConfigPath);
	return ConfigList;
}
