#include "FHttpHelper.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void FHttpHelper::HttpRequestGet(const FString& Url)
{
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest;
	HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb(TEXT("Get"));
	HttpRequest->SetURL(Url);
	HttpRequest->SetHeader(TEXT("User-Agent"),TEXT("UnrealEngine"));
	HttpRequest->SetHeader(TEXT("Content-Type"),TEXT("application/Json"));
	HttpRequest->OnProcessRequestComplete().BindRaw(this,&FHttpHelper::OnRequestComploteGet);
	HttpRequest->ProcessRequest();
}

void FHttpHelper::HttpRequestPost(const FString& Url, const FString& Msg)
{
	TSharedPtr<IHttpRequest,ESPMode::ThreadSafe> HttpRequest;
	HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb(TEXT("Post"));
	HttpRequest->SetURL(Url);
	HttpRequest->SetHeader(TEXT("User-Agent"),TEXT("UnrealEngine"));
	HttpRequest->SetHeader(TEXT("Content-Type"),TEXT("application/Json"));
	HttpRequest->SetContentAsString(Msg);
	HttpRequest->OnProcessRequestComplete().BindRaw(this,&FHttpHelper::OnRequestComplotePost);
	HttpRequest->ProcessRequest();
}

void FHttpHelper::OnRequestComplotePost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		if (Response->GetResponseCode() == EHttpResponseCodes::Ok)
		{
			UE_LOG(LogTemp, Log, TEXT("%s"),*Response->GetContentAsString());
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("HttpError"))
		}
	}	
}

void FHttpHelper::OnRequestComploteGet(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		if (Response->GetResponseCode() == EHttpResponseCodes::Ok)
		{
			UE_LOG(LogTemp, Log, TEXT("%s"),*Response->GetContentAsString());
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("HttpError"))
		}
	}
}
