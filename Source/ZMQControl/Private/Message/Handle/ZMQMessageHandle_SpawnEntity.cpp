// Fill out your copyright notice in the Description page of Project Settings.

#include "Message/Handle/ZMQMessageHandle_SpawnEntity.h"

#include "ZMQControlTypes.h"

UZMQMessageHandle_SpawnEntity::UZMQMessageHandle_SpawnEntity()
{
	MessageTag = GameplayTags::Message_SpawnEntity;
}

void UZMQMessageHandle_SpawnEntity::OnReceiveMessage(const FString& InData)
{
	Super::OnReceiveMessage(InData);

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(InData);

	TSharedPtr<FJsonObject> JsonObject;
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UClass* Class = nullptr;
		FVector Location = FVector::ZeroVector;
		FRotator Rotation = FRotator::ZeroRotator;
		FVector Scale = FVector::ZeroVector;
		
		if(JsonObject->HasField(TEXT("class")))
		{
			const FString Field = JsonObject->GetStringField(TEXT("class"));
			Class = LoadClass<AActor>(nullptr, *Field);
		}
		if(JsonObject->HasField(TEXT("location")))
		{
			const FString Field = JsonObject->GetStringField(TEXT("location"));
			TArray<FString> Fields;
			if(Field.ParseIntoArray(Fields, TEXT(",")) >= 3)
			{
				Location = FVector(FCString::Atof(*Fields[0]), FCString::Atof(*Fields[1]), FCString::Atof(*Fields[2]));
			}
		}
		if(JsonObject->HasField(TEXT("rotation")))
		{
			const FString Field = JsonObject->GetStringField(TEXT("rotation"));
			TArray<FString> Fields;
			if(Field.ParseIntoArray(Fields, TEXT(",")) >= 3)
			{
				Rotation = FRotator(FCString::Atof(*Fields[0]), FCString::Atof(*Fields[1]), FCString::Atof(*Fields[2]));
			}
		}
		if(JsonObject->HasField(TEXT("scale")))
		{
			const FString Field = JsonObject->GetStringField(TEXT("scale"));
			TArray<FString> Fields;
			if(Field.ParseIntoArray(Fields, TEXT(",")) >= 3)
			{
				Scale = FVector(FCString::Atof(*Fields[0]), FCString::Atof(*Fields[1]), FCString::Atof(*Fields[2]));
			}
		}
		
		if (Class)
		{
			AActor* Entity = GetWorld()->SpawnActor(Class);
			if(Entity)
			{
				Entity->SetActorLocation(Location);
				Entity->SetActorRotation(Rotation);
				Entity->SetActorScale3D(Scale);
			}
		}
	}
}
