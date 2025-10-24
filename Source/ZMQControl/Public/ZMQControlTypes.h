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
	ZMQCONTROL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_DestroyEntity);
	
	ZMQCONTROL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_PlaySound);
	ZMQCONTROL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_StopSound);
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

USTRUCT(BlueprintType)
struct FZMQStatusCode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZMQ")
	int32 StatusCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZMQ")
	FString Message;

	FZMQStatusCode() : StatusCode(0), Message(TEXT("")) {}
	FZMQStatusCode(int32 InCode, const FString& InMessage) : StatusCode(InCode), Message(InMessage) {}
	
};

struct FZMQStatus
{
	static const FZMQStatusCode SUCCESS;		//200 成功
	static const FZMQStatusCode CREATED;		//201 创建成功
	static const FZMQStatusCode EXISTED;		//202 已存在
	static const FZMQStatusCode NOT_FOUND;		//404 找不到
	static const FZMQStatusCode TIMEOUT;		//408 超时
	static const FZMQStatusCode BAD_REQUEST;	//400 参数错误
	static const FZMQStatusCode SERVER_ERROR;	//500 内部服务错误
	static const FZMQStatusCode UNKNOW_ERROR;	//101 未知错误
};
