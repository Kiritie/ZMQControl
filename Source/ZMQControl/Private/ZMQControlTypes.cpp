// Fill out your copyright notice in the Description page of Project Settings.

#include "ZMQControlTypes.h"

namespace GameplayTags
{
	////////////////////////////////////////////////////
	// Messages
	UE_DEFINE_GAMEPLAY_TAG(Message_SpawnEntity, "Message.SpawnEntity");
	UE_DEFINE_GAMEPLAY_TAG(Message_SpawnDynamicEntity, "Message.SpawnDynamicEntity");
	UE_DEFINE_GAMEPLAY_TAG(Message_DestroyEntity, "Message.DestroyEntity");

	UE_DEFINE_GAMEPLAY_TAG(Message_PlaySound, "Message.PlaySound");
	UE_DEFINE_GAMEPLAY_TAG(Message_StopSound, "Message.StopSound");
}

const FZMQStatusCode FZMQStatus::SUCCESS(200, TEXT("Success"));
const FZMQStatusCode FZMQStatus::CREATED(201, TEXT("Created"));
const FZMQStatusCode FZMQStatus::EXISTED(202, TEXT("Created Failed"));
const FZMQStatusCode FZMQStatus::NOT_FOUND(404, TEXT("Not Found"));
const FZMQStatusCode FZMQStatus::TIMEOUT(408, TEXT("Request Timeout"));
const FZMQStatusCode FZMQStatus::SERVER_ERROR(500, TEXT("Internal Server Error"));
const FZMQStatusCode FZMQStatus::UNKNOW_ERROR(101, TEXT("UnKnow Error"));
