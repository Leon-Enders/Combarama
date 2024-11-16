#pragma once
#include <chrono>
#include <functional>
#include "../Coroutine.h"


//Awaitable which suspends for the set Delay(in Seconds) on the main thread
class WaitSeconds
{
public:
    WaitSeconds(float Delay) : TimeRemaining(Delay) {}

  
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<Coroutine::promise_type> InHandle)
    {
        
        Handle = InHandle;

    }
    void await_resume() {}

private:
  
    float TimeRemaining = 0.f;
    std::coroutine_handle<Coroutine::promise_type> Handle;
};