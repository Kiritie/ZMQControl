// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#include "Entity/ZMQEntityManager.h"

#include "ZMQControlStatics.h"
#include "ZMQControlTypes.h"
#include "Message/ZMQMessageManager.h"

// Sets default values
AZMQEntityManager::AZMQEntityManager()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));

	MessageManagers = TArray<UZMQMessageManager*>();
	MessageManagerMap = TMap<FString, UZMQMessageManager*>();
}

void AZMQEntityManager::OnInitialize()
{
	K2_OnInitialize();

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
		}
	}
}

void AZMQEntityManager::OnRefresh(float DeltaSeconds)
{
	K2_OnRefresh(DeltaSeconds);

	for(const auto Iter : MessageManagerMap)
	{
		Iter.Value->OnRefresh(DeltaSeconds);
	}
}

void AZMQEntityManager::OnTermination()
{
	K2_OnTermination();

	for(const auto Iter : MessageManagerMap)
	{
		Iter.Value->OnTermination();
	}
}

void AZMQEntityManager::BeginPlay()
{
	Super::BeginPlay();

	OnInitialize();
}

void AZMQEntityManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnTermination();
}

void AZMQEntityManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OnRefresh(DeltaTime);
}

TArray<UZMQMessageManager*> AZMQEntityManager::GetMessageManagers() const
{
	TArray<UZMQMessageManager*> ReturnValues;
	MessageManagerMap.GenerateValueArray(ReturnValues);
	return ReturnValues;
}

UZMQMessageManager* AZMQEntityManager::GetMessageManagerByName(const FString& InName) const
{
	if(MessageManagerMap.Contains(InName))
	{
		return MessageManagerMap[InName];
	}
	return nullptr;
}
