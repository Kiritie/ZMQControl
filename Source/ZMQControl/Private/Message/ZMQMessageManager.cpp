// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#include "Message/ZMQMessageManager.h"

#include "ZMQ/zmq.hpp"
#include "Message/Handle/ZMQMessageHandleBase.h"

// Sets default values
UZMQMessageManager::UZMQMessageManager()
{
	ManagerName = TEXT("");
	ChannelType = 0;
	ServerURL = TEXT("");
	MessageHandles = TArray<UZMQMessageHandleBase*>();
	MessageHandleMap = TMap<FGameplayTag, UZMQMessageHandleBase*>();
}

void UZMQMessageManager::OnInitialize()
{
	K2_OnInitialize();

	for(const auto Iter : MessageHandles)
	{
		MessageHandleMap.Add(Iter->GetMessageTag(), Iter);
	}
}

void UZMQMessageManager::OnRefresh(float DeltaSeconds)
{
	K2_OnRefresh(DeltaSeconds);
	
	if(bIsWorking)
	{
		DoWork();
	}
}

void UZMQMessageManager::OnReceiveMessage(const FGameplayTag& InTag, const FString& InData)
{
	K2_OnReceiveMessage(InTag, InData);
	
	if(UZMQMessageHandleBase* MessageHandle = GetMessageHandleByTag(InTag))
	{
		MessageHandle->OnReceiveMessage(InData);
	}
}

void UZMQMessageManager::OnTermination()
{
	K2_OnTermination();

	StopWork();
	
	zmq_close(Scriber);
	zmq_ctx_term(Context);
}

void UZMQMessageManager::Connect(const FZMQConnectInfo& InInfo)
{
	if(Context)
	{
		UE_LOG(LogTemp, Warning, TEXT("A ZMQ connection has been established, name is %s"), *InInfo.Name)
		return;
	}
	
	Context = zmq_ctx_new();
	
	zmq_ctx_set(Context, ZMQ_MAX_SOCKETS, 1);
	
	Scriber = zmq_socket(Context, InInfo.ChannelType);
	
	if(InInfo.ChannelType == ZMQ_REP)
	{
		zmq_bind(Scriber, TCHAR_TO_UTF8(*InInfo.ServerURL));
	}
	else
	{
		zmq_connect(Scriber, TCHAR_TO_UTF8(*InInfo.ServerURL));
	}
	if(InInfo.ChannelType == ZMQ_SUB)
	{
		zmq_setsockopt(Scriber, ZMQ_SUBSCRIBE, nullptr, 0);
	}
}

void UZMQMessageManager::StartWork()
{
	bIsWorking = true;
}

void UZMQMessageManager::DoWork()
{
	char MessageTag[50];
	int Ret = zmq_recv(Scriber, MessageTag, 50, ZMQ_DONTWAIT);
	if (-1 != Ret)
	{
		MessageTag[Ret] = '\0';
	}
	else
	{
		return;
	}
	
	char MessageData[20491];
	Ret = zmq_recv(Scriber, MessageData, 20491, ZMQ_DONTWAIT);
	if(-1 != Ret)
	{
		MessageData[Ret] = '\0';
	}
	else
	{
		return;
	}
	
	OnReceiveMessage(FGameplayTag::RequestGameplayTag(MessageTag), MessageData);
}

void UZMQMessageManager::StopWork()
{
	bIsWorking = false;
}

void UZMQMessageManager::SendMessage(const FString& InData)
{
	if(Scriber)
	{
		zmq_send(Scriber, TCHAR_TO_UTF8(*InData), strlen(TCHAR_TO_UTF8(*InData)), 0);
	}
}

TArray<UZMQMessageHandleBase*> UZMQMessageManager::GetMessageHandles() const
{
	TArray<UZMQMessageHandleBase*> ReturnValues;
	MessageHandleMap.GenerateValueArray(ReturnValues);
	return ReturnValues;
}

UZMQMessageHandleBase* UZMQMessageManager::GetMessageHandleByTag(const FGameplayTag& InTag) const
{
	if(MessageHandleMap.Contains(InTag))
	{
		return MessageHandleMap[InTag];
	}
	return nullptr;
}
