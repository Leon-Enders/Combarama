#pragma once

#include <utility>
#include <vector>
#include "Task.h"





class CoroutineSystem
{
public:

    
    static CoroutineSystem& Get() { return Instance; }

    void Tick(float DeltaTime);

    
    void RegisterCoroutine(std::coroutine_handle<Task::promise_type> handle, float delay)
    {
        Coroutines.emplace_back(handle, delay);
    }


private:
    
    static CoroutineSystem Instance;


    std::vector<std::pair<std::coroutine_handle<Task::promise_type>, float>> Coroutines;
};