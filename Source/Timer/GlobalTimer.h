#pragma once

#include "../Event/Delegate.h"



class GlobalTimer
{
public:
	static GlobalTimer& Get() { return Instance; }

	void Tick(float DeltaTime);


	const std::function<void(float)>& AddTicker(const std::function<void(float)>& FunctionToBind);
	void RemoveTicker(const std::function<void(float)>& FunctionToRemove);

private:
	static GlobalTimer Instance;

	MulticastDelegate<void, float> TimedCallbacks;
};