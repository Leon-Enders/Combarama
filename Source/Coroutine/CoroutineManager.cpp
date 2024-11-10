#include "CoroutineManager.h"

CoroutineManager CoroutineManager::Instance;

void CoroutineManager::StartCoroutine(Task&& Coroutine)
{
	ActiveCoroutines.push_back(std::move(Coroutine));
	ActiveCoroutines.back().Handle.resume();
}
