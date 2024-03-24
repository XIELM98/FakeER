#include "FMyRunnable.h"

bool FMyRunnable::Init()
{
	return true;
	
}

uint32 FMyRunnable::Run()
{
	
	return  0;
}

void FMyRunnable::Stop()
{
	FRunnable::Stop();
}

void FMyRunnable::Exit()
{
	FRunnable::Exit();
}
