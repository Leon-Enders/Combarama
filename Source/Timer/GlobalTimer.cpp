#include "GlobalTimer.h"


GlobalTimer GlobalTimer::Instance;


void GlobalTimer::Tick(float DeltaTime)
{
	
	TimedCallbacks.Broadcast(DeltaTime);
}

const std::function<void(float)>& GlobalTimer::AddTicker(const std::function<void(float)>& FunctionToBind)
{
	TimedCallbacks.AddFunction(FunctionToBind);
	return FunctionToBind;
}

void GlobalTimer::RemoveTicker(const std::function<void(float)>& FunctionToRemove)
{
	TimedCallbacks.UnSubscribe(FunctionToRemove);
}
