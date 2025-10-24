// Copyright 2020-2021 CesiumGS, Inc. and Contributors
#pragma once
#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "ZMQControlTypes.h"
#include "ZMQMessageManager.generated.h"

class UZMQMessageHandle;

UCLASS(Blueprintable, EditInlineNew)
class ZMQCONTROL_API UZMQMessageManager : public UObject
{
	GENERATED_BODY()

public:
	UZMQMessageManager();

public:
	/**
	* 当初始化
	*/
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnInitialize")
	void K2_OnInitialize();
	UFUNCTION()
	virtual void OnInitialize();
	/**
	* 当刷新
	*/
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnRefresh")
	void K2_OnRefresh(float DeltaSeconds);
	UFUNCTION()
	virtual void OnRefresh(float DeltaSeconds);
	/**
	* 当接收消息
	*/
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnReceiveMessage")
	void K2_OnReceiveMessage(const FGameplayTag& InTag, const FString& InData);
	UFUNCTION(BlueprintCallable)
	void OnReceiveMessage(const FGameplayTag& InTag, const FString& InData);
	/**
	* 当销毁
	*/
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnTermination")
	void K2_OnTermination();
	UFUNCTION()
	virtual void OnTermination();

public:
	UFUNCTION(BlueprintCallable)
	void Connect(const FZMQConnectInfo& InInfo);

	UFUNCTION(BlueprintCallable)
	void StartWork();

	UFUNCTION(BlueprintCallable)
	void DoWork();

	UFUNCTION(BlueprintCallable)
	void StopWork();

	UFUNCTION(BlueprintCallable)
	void SendMessage(const FString& InData);

protected:
	UPROPERTY(EditAnywhere)
	FString ManagerName;

	UPROPERTY(VisibleAnywhere)
	int32 ChannelType;

	UPROPERTY(VisibleAnywhere)
	FString ServerURL;

	UPROPERTY(EditAnywhere, Instanced)
	TArray<UZMQMessageHandle*> MessageHandles;

	UPROPERTY(VisibleAnywhere)
	TMap<FGameplayTag, UZMQMessageHandle*> MessageHandleMap;

	UPROPERTY(VisibleAnywhere)
	bool bIsWorking;
	
	void* Scriber;
	
	void* Context;

public:
	UFUNCTION(BlueprintPure)
	FString GetManagerName() const { return ManagerName; }

	UFUNCTION(BlueprintPure)
	TArray<UZMQMessageHandle*> GetMessageHandles() const;

	UFUNCTION(BlueprintPure)
	UZMQMessageHandle* GetMessageHandleByTag(const FGameplayTag& InTag) const;

	UFUNCTION(BlueprintCallable, Category = "ZMQ")
	void SendStatusToServer(const FZMQStatusCode& Status, const FString& InData);
};
