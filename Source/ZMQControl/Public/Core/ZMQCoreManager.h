// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ZMQCoreManager.generated.h"

class UZMQMessageManager;

UCLASS(Blueprintable)
class ZMQCONTROL_API AZMQCoreManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AZMQCoreManager();

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
	* 当销毁
	*/
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnTermination")
	void K2_OnTermination();
	UFUNCTION()
	virtual void OnTermination();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Instanced)
	TArray<UZMQMessageManager*> MessageManagers;

	UPROPERTY(VisibleAnywhere)
	TMap<FString, UZMQMessageManager*> MessageManagerMap;

public:
	UFUNCTION(BlueprintPure)
	TArray<UZMQMessageManager*> GetMessageManagers() const;

	UFUNCTION(BlueprintPure)
	UZMQMessageManager* GetMessageManagerByName(const FString& InName) const;
};
