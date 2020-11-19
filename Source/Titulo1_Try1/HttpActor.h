// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "HttpModule.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Templates/SharedPointer.h"
#include "Containers/UnrealString.h"
#include "Containers/Array.h"

#include "HttpActor.generated.h"

UCLASS()
class TITULO1_TRY1_API AHttpActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHttpActor();

	FHttpModule* Http;

	UFUNCTION(BlueprintCallable, Category = "API REST")
		void GET_Request();

	UFUNCTION(BlueprintCallable, Category = "API REST")
		void POST_Request(TArray<FString> valuesArray);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
