#pragma once
#include <vector>
#include <coroutine>
#include <optional>
#include "Task.h"

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