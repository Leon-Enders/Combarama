#pragma once
#include <chrono>
#include <functional>
#include <SDL3/SDL_timer.h>
#include "../CoroutineSystem.h"
#include "../../Timer/GlobalTimer.h"



class WaitSeconds
{
public:
    WaitSeconds(float Delay) : TimeRemaining(Delay) {}

  
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<Task::promise_type> InHandle)
    {
        
        Handle = InHandle;

        //CoroutineSystem::Get().RegisterCoroutine(InHandle, Delay);


        TickerHandle = GlobalTimer::Get().AddTicker([this](float DeltaTime)
            {
                TimeRemaining -= DeltaTime;
                if (TimeRemaining <= 0.f)
                {
                    GlobalTimer::Get().RemoveTicker(TickerHandle);
                    Handle.resume();
                }
            });

    }
    void await_resume() {}

private:
    //float Delay = 0.f;
    //float TargetTime = 0.f;
    float TimeRemaining = 0.f;
    std::coroutine_handle<Task::promise_type> Handle;
    std::function<void(float)> TickerHandle;
};