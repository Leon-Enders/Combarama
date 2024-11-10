#pragma once
#include <chrono>
#include <SDL3/SDL_timer.h>
#include "../CoroutineSystem.h"



class WaitSeconds
{
public:
    WaitSeconds(float InDelay) : Delay(InDelay) {}

  
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<Task::promise_type> InHandle)
    {
        TargetTime = static_cast<float>(SDL_GetTicksNS()) + Delay;
        Handle = InHandle;

        CoroutineSystem::Get().RegisterCoroutine(InHandle, Delay);
    }
    void await_resume() {}

private:
    float Delay = 0.f;
    float TargetTime = 0.f;
    std::coroutine_handle<Task::promise_type> Handle;
};