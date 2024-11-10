#pragma once
#include <chrono>
#include <SDL3/SDL_timer.h>
#include "../Task.h"



class WaitSeconds
{
public:
    WaitSeconds(float InDelay) : Delay(InDelay) {}

  
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<Task::promise_type> InHandle)
    {
        TargetTime = static_cast<float>(SDL_GetTicksNS()) + Delay;
        Handle = InHandle;
    }
    void await_resume() {}


    void check_and_resume() 
    {
        if (Handle && static_cast<float>(SDL_GetTicksNS()) >= TargetTime)
        {
            Handle.resume();
        }
    }

private:
    float Delay = 0.f;
    float TargetTime = 0.f;
    std::coroutine_handle<Task::promise_type> Handle;
};