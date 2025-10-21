// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ZMQMessageHandleBase.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ZMQCONTROL_API UZMQMessageHandleBase : public UObject
{
	GENERATED_BODY()

public:
	UZMQMessageHandleBase();

public:
	/**
	* 当接收消息
	*/
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnReceiveMessage")
	void K2_OnReceiveMessage(const FString& InData);
	virtual void OnReceiveMessage(const FString& InData);

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag MessageTag;

public:
	UFUNCTION(BlueprintPure)
	FGameplayTag GetMessageTag() const { return MessageTag; }
};
