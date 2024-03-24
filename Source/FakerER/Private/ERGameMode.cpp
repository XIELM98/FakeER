// Fill out your copyright notice in the Description page of Project Settings.


#include "ERGameMode.h"

#include "ERHUD.h"
#include "Characters/Player/ERPlayerCharacter.h"
#include "ERPlayerController.h"
#include "FHttpHelper.h"
#include "FMyRunnable.h"
#include "Actors/SceneItemsActor.h"
#include "Kismet/GameplayStatics.h"

AERGameMode::AERGameMode()
{
	TSubclassOf<AERPlayerCharacter> PlayerClass = LoadClass<AERPlayerCharacter>(nullptr,TEXT("/Script/Engine.Blueprint'/Game/FakeER/BluePrints/Player/BP_Player.BP_Player_C'"));
	DefaultPawnClass = PlayerClass;
	PlayerControllerClass = AERPlayerController::StaticClass();
	HUDClass = LoadClass<AERHUD>(nullptr,TEXT("/Script/Engine.Blueprint'/Game/FakeER/BluePrints/Player/BP_ERHUD.BP_ERHUD_C'"));
}

void AERGameMode::RequestHttpGet(const FString& Url)
{
	if (!HttpHelper)
	{
		HttpHelper = MakeShareable(new FHttpHelper);
	}
	HttpHelper->HttpRequestGet(Url);
}

void AERGameMode::RequestHttpPost(const FString& Url,const FString& Msg)
{
	if (!HttpHelper)
	{
		HttpHelper = MakeShareable(new FHttpHelper);
	}
	HttpHelper->HttpRequestPost(Url,Msg);
}

void AERGameMode::MyThread()
{
	if (!MyRunnable)
	{
		MyRunnable = MakeShareable(new FMyRunnable);
	}
	FRunnableThread::Create(MyRunnable.Get(),TEXT("MyThread"));
}

// void AERGameMode::SetJson()
// {
// 	FString Json;
// 	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Json);
// 	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
// 	JsonObject->SetStringField(TEXT("name"),TEXT("aaa"));
// 	JsonObject->SetNumberField(TEXT("age"),10);
//
// 	TArray<TSharedPtr<FJsonValue>> JsonValue;
// 	JsonValue.Add(MakeShareable(new FJsonValueString(TEXT("x"))));
// 	JsonValue.Add(MakeShareable(new FJsonValueString(TEXT("y"))));
// 	JsonValue.Add(MakeShareable(new FJsonValueString(TEXT("z"))));
// 	JsonValue.Add(MakeShareable(new FJsonValueNumber(20)));
// 	JsonObject->SetArrayField(TEXT("str"),JsonValue);
// 	
// 	FJsonSerializer::Serialize(JsonObject.ToSharedRef(),JsonWriter);
// 	FFileHelper::SaveStringToFile(Json,TEXT(":\\1.json"));
// }
//
// void AERGameMode::SetActor()
// {
// 	TArray<AActor*> Items;
// 	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AActor::StaticClass(),Items);
// 	FString Json;
// 	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Json);
// 	TArray<TSharedPtr<FJsonValue>> JsonValues;
// 	for (auto key: Items)
// 	{
// 		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
// 		JsonObject->SetStringField(TEXT("name"),key->GetName());
// 		TSharedPtr<FJsonObject> Location = MakeShareable(new FJsonObject);
// 		Location->SetNumberField(TEXT("x"),key->GetActorLocation().X);
// 		Location->SetNumberField(TEXT("y"),key->GetActorLocation().Y);
// 		Location->SetNumberField(TEXT("z"),key->GetActorLocation().Z);
// 		JsonObject->SetObjectField(TEXT("location"),Location);
// 		JsonValues.Add(MakeShareable(new FJsonValueObject(JsonObject)));
// 	}
// 	if (FJsonSerializer::Serialize(JsonValues,JsonWriter))
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("11"))		
// 	}
// 	
// 	FFileHelper::SaveStringToFile(Json,TEXT("d:\\2.json"));
// }
//
// void AERGameMode::GetJson()
// {
// 	FString Json;
// 	if (FFileHelper::LoadFileToString(Json,TEXT("d:\\1.json")))
// 	{
// 		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Json);
// 		TSharedPtr<FJsonObject> JsonObject;
// 		if (FJsonSerializer::Deserialize(JsonReader,JsonObject))
// 		{
// 		
// 			TArray<TSharedPtr<FJsonValue>> str = JsonObject->GetArrayField(TEXT("str"));
// 			for (auto key : str)
// 			{
// 				UE_LOG(LogTemp, Log, TEXT("%s"),*key->AsString())
// 			}
// 		}
// 	}
// }
