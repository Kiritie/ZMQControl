// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "ZMQControlTypes.generated.h"

namespace GameplayTags
{
	////////////////////////////////////////////////////
	// Messages
	ZMQCONTROL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_SpawnEntity);
}

USTRUCT(BlueprintType)
struct FZMQConnectInfo
{
	GENERATED_BODY()

public:
	FZMQConnectInfo()
	{
		Name = TEXT("");
		ChannelType = 0;
		ServerURL = TEXT("");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ChannelType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ServerURL;
};
