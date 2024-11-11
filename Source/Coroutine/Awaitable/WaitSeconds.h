#pragma once
#include <chrono>
#include <functional>
#include <SDL3/SDL_timer.h>
#include "../../Timer/GlobalTimer.h"


//Awaitable which suspends for the set Delay(in Seconds) on the main thread
class WaitSeconds
{
public:
    WaitSeconds(float Delay) : TimeRemaining(Delay) {}
   
  
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<Task::promise_type> InHandle)
    {
        Handle = InHandle;


        auto Callback = [this](float DeltaTime) -> void
            {
                TimeRemaining -= DeltaTime;
                if (TimeRemaining <= 0.f)
                {
                    GlobalTimer::Get().RemoveTicker(CallbackPtr);
                    Handle.resume();
                }
            };

        std::function<void(float)> WrappedCallback = Callback;
        CallbackPtr = std::make_shared<std::function<void(float)>>(WrappedCallback);


        GlobalTimer::Get().AddTicker(CallbackPtr);
    }
    void await_resume() {}

private:
  
    float TimeRemaining = 0.f;
    std::coroutine_handle<Task::promise_type> Handle;
    std::shared_ptr<std::function<void(float)>> CallbackPtr;
};