// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#include "Core/ZMQCoreManager.h"

#include "ZMQControlStatics.h"
#include "ZMQControlTypes.h"
#include "Message/ZMQMessageManager.h"
#include "ZMQ/zmq.h"

AZMQCoreManager* AZMQCoreManager::Instance = nullptr;

// Sets default values
AZMQCoreManager::AZMQCoreManager()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));

	MessageManagers = TArray<UZMQMessageManager*>();
	MessageManagerMap = TMap<FString, UZMQMessageManager*>();
}

AZMQCoreManager* AZMQCoreManager::Get()
{
	return Instance;
}

void AZMQCoreManager::OnInitialize()
{
	K2_OnInitialize();

	Instance = this;

	for(const auto Iter : MessageManagers)
	{
		Iter->OnInitialize();
		MessageManagerMap.Add(Iter->GetManagerName(), Iter);
	}

	for(auto Iter : UZMQControlStatics::GetZMQConnectInfos())
	{
		if(UZMQMessageManager* MessageManager = GetMessageManagerByName(Iter.Name))
		{
			MessageManager->Connect(Iter);
			MessageManager->StartWork();
			// switch (Iter.ChannelType)
			// {
			// 	case ZMQ_REP:
			// 	case ZMQ_SUB:
			// 		MessageManager->StartWork();
			// 		UE_LOG(LogTemp, Log, TEXT("[ZMQ] Started receiving on channel: %s (type=%d)"),*Iter.Name,Iter.ChannelType);
			// 		break;
			// 	case ZMQ_REQ:
			// 	case ZMQ_PUB:
			// 		UE_LOG(LogTemp, Log, TEXT("[ZMQ] Initialized send-only channel: %s (type=%d)"), *Iter.Name, Iter.ChannelType);
			// 		break;
			// 	default:
			// 		UE_LOG(LogTemp, Warning, TEXT("[ZMQ] Unknown channel type for %s: %d"), *Iter.Name, Iter.ChannelType);
			// 		break;
			// }
		}
	}
}

void AZMQCoreManager::OnRefresh(float DeltaSeconds)
{
	K2_OnRefresh(DeltaSeconds);

	for(const auto Iter : MessageManagerMap)
	{
		Iter.Value->OnRefresh(DeltaSeconds);
	}
}

void AZMQCoreManager::OnTermination()
{
	K2_OnTermination();

	Instance = nullptr;

	for(const auto Iter : MessageManagerMap)
	{
		Iter.Value->OnTermination();
	}
}

void AZMQCoreManager::BeginPlay()
{
	Super::BeginPlay();

	OnInitialize();
}

void AZMQCoreManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnTermination();
}

void AZMQCoreManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OnRefresh(DeltaTime);
}

TArray<UZMQMessageManager*> AZMQCoreManager::GetMessageManagers() const
{
	TArray<UZMQMessageManager*> ReturnValues;
	MessageManagerMap.GenerateValueArray(ReturnValues);
	return ReturnValues;
}

UZMQMessageManager* AZMQCoreManager::GetMessageManagerByName(const FString& InName) const
{
	if(MessageManagerMap.Contains(InName))
	{
		return MessageManagerMap[InName];
	}
	return nullptr;
}
