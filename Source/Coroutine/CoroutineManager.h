#pragma once
#include <vector>
#include <coroutine>
#include "Task.h"

class CoroutineManager
{
public:
	static CoroutineManager& Get() { return Instance; }
	

	void StartCoroutine(Task&& Coroutine);


private:
	static CoroutineManager Instance;

	std::vector<Task> ActiveCoroutines;
};