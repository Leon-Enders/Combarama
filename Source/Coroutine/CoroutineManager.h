#pragma once
#include <vector>
#include <coroutine>
#include <optional>
#include "Task.h"

//Singleton Object which should own, start and manage the lifetime of all Coroutines 
class CoroutineManager
{
public:
	static CoroutineManager& Get() { return Instance; }
	

	void StartCoroutine(Task&& Coroutine);

	void CleanupCompletedCoroutines();

private:
	static CoroutineManager Instance;

	std::vector<std::optional<Task>> ActiveCoroutines;
};