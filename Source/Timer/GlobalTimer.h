#pragma once

#include <vector>
#include <functional>
#include <memory>

//Singleton Object for triggering callbacks on tick
//TODO: Update Class to be able to Trigger callbacks with a desired Interval

class GlobalTimer
{
public:
	static GlobalTimer& Get() { return Instance; }

	void Tick(float DeltaTime);

	void AddTicker(std::shared_ptr<std::function<void(float)>> CallbackToAdd);
	void RemoveTicker(std::shared_ptr<std::function<void(float)>> CallbackToRemove);

private:
	static GlobalTimer Instance;

	std::vector<std::shared_ptr<std::function<void(float)>>> Callbacks;
};