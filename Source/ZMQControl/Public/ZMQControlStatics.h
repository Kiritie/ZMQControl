// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZMQControlTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "ZMQControlStatics.generated.h"

/**
 * 
 */
UCLASS()
class ZMQCONTROL_API UZMQControlStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ZMQControlStatics")
	static TArray<FZMQConnectInfo> GetZMQConnectInfos();
};
