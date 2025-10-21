// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#include "Message/Handle/ZMQMessageHandleBase.h"

UZMQMessageHandleBase::UZMQMessageHandleBase()
{
	MessageTag = FGameplayTag::EmptyTag;
}

void UZMQMessageHandleBase::OnReceiveMessage(const FString& InData)
{

}
