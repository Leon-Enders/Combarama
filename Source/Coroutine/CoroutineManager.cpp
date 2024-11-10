#include "CoroutineManager.h"

CoroutineManager CoroutineManager::Instance;

void CoroutineManager::StartCoroutine(Task&& Coroutine)
{
	ActiveCoroutines.push_back(std::move(Coroutine));
	ActiveCoroutines.back()->Resume();
}

void CoroutineManager::CleanupCompletedCoroutines()
{
    bool NeedCleanup = false;
    for (auto& TaskOpt : ActiveCoroutines) 
    {
        if (TaskOpt && TaskOpt->IsDone())
        {
            NeedCleanup = true;
            TaskOpt.reset();
        }
    }

    if (NeedCleanup)
    {
        ActiveCoroutines.erase(std::remove(ActiveCoroutines.begin(), ActiveCoroutines.end(), std::nullopt), ActiveCoroutines.end());
    }
}
