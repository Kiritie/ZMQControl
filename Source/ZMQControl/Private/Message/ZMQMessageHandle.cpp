// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#include "Message/ZMQMessageHandle.h"

UZMQMessageHandle::UZMQMessageHandle()
{
	MessageTag = FGameplayTag::EmptyTag;
}

void UZMQMessageHandle::OnReceiveMessage(const FString& InData)
{

}
