#pragma once
#include "Interfaces/IHttpRequest.h"

class FHttpHelper
{
public:
	void HttpRequestGet(const FString& Url);
	void HttpRequestPost(const FString& Url, const FString& Msg);

protected:
	void OnRequestComploteGet(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnRequestComplotePost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};
