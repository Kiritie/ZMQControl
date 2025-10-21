// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#include "Entity/ZMQEntityBase.h"

// Sets default values
AZMQEntityBase::AZMQEntityBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
}

void AZMQEntityBase::OnInitialize()
{
	K2_OnInitialize();
}

void AZMQEntityBase::OnRefresh(float DeltaSeconds)
{
	K2_OnRefresh(DeltaSeconds);
}

void AZMQEntityBase::OnTermination()
{
	K2_OnTermination();
}

void AZMQEntityBase::BeginPlay()
{
	Super::BeginPlay();

	OnInitialize();
}

void AZMQEntityBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnTermination();
}

void AZMQEntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OnRefresh(DeltaTime);
}
