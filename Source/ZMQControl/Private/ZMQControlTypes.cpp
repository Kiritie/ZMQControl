// Fill out your copyright notice in the Description page of Project Settings.

#include "ZMQControlTypes.h"

namespace GameplayTags
{
	////////////////////////////////////////////////////
	// Messages
	UE_DEFINE_GAMEPLAY_TAG(Message_SpawnEntity, "Message.SpawnEntity");
	UE_DEFINE_GAMEPLAY_TAG(Message_DestroyEntity, "Message.DestroyEntity");

	UE_DEFINE_GAMEPLAY_TAG(Message_PlaySound, "Message.PlaySound");
	UE_DEFINE_GAMEPLAY_TAG(Message_StopSound, "Message.StopSound");
}
