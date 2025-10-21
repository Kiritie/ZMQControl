// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZMQMessageHandleBase.h"
#include "ZMQMessageHandle_SpawnEntity.generated.h"

/**
 * 
 */
UCLASS()
class ZMQCONTROL_API UZMQMessageHandle_SpawnEntity : public UZMQMessageHandleBase
{
	GENERATED_BODY()

public:
	UZMQMessageHandle_SpawnEntity();

public:
	virtual void OnReceiveMessage(const FString& InData) override;
};
