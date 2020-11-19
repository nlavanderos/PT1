// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpActor.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Templates/SharedPointer.h"
#include "Dom/JsonObject.h"
#include "JsonUtilities.h"
#include "Json.h"

#include "Containers/Array.h"
#include "Containers/UnrealString.h"

// Sets default values
AHttpActor::AHttpActor() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AHttpActor::BeginPlay() {
	Super::BeginPlay();
	Http = &FHttpModule::Get();
}

void AHttpActor::GET_Request() {
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	Request->SetURL("https://dashboard.gemusei.org/playerstat/"); //URL API
	Request->SetVerb("GET");
}

void AHttpActor::POST_Request(TArray<FString> valuesArray) {
	FString ContentJsonString;

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	Request->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnResponseReceived);

	Request->SetURL("https://dashboard.gemusei.org/playerstat/"); //URL API
	//Request->SetURL("http://127.0.0.1:8000/gamedata/"); //URL API

	//Headers
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	JsonObject->SetStringField("player", valuesArray[0]);
	JsonObject->SetStringField("session", valuesArray[1]);
	JsonObject->SetStringField("level", valuesArray[2]);
	JsonObject->SetStringField("action", valuesArray[3]);
	JsonObject->SetStringField("time", valuesArray[4]);
	JsonObject->SetStringField("state", valuesArray[5]);

	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&ContentJsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	//POST Request
	Request->SetVerb("POST");
	Request->SetContentAsString(ContentJsonString);
	Request->ProcessRequest();
}

void AHttpActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		GLog->Log("Se recibio la siguiente respuesta: ");
		GLog->Log(Response->GetContentAsString());
	}
}
