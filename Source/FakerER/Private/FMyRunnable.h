#pragma once
#include "CoreMinimal.h"


class FMyRunnable : public FRunnable
{
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
};
