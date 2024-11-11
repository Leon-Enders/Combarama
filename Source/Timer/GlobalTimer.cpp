#include "GlobalTimer.h"
#include <ranges>


GlobalTimer GlobalTimer::Instance;


void GlobalTimer::Tick(float DeltaTime)
{
	for (auto& Callback : Callbacks)
	{
		if (Callback)
		{
			(*Callback)(DeltaTime);
		};
	}
}

void GlobalTimer::AddTicker(std::shared_ptr<std::function<void(float)>> CallbackToAdd)
{
	Callbacks.push_back(CallbackToAdd);
}

void GlobalTimer::RemoveTicker(std::shared_ptr<std::function<void(float)>> CallbackToRemove)
{
	std::erase_if(Callbacks, [&](std::shared_ptr<std::function<void(float)>>& Callback)
		{
			return Callback.get() == CallbackToRemove.get();
		});
}
