#pragma once
#include <chrono>
#include <functional>
#include <experimental/generator>
#include "../Coroutine.h"


//Awaitable which suspends for the set Delay(in Seconds) on the main thread
class WaitSeconds
{
public:
    WaitSeconds(float InDuration) : Duration(InDuration) {}

  
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<Coroutine::promise_type> InHandle)
    {
        Handle = InHandle;
        auto DurationNS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(Duration));
        SleepGenerator = SleepFor(DurationNS);
        SleepIterator = SleepGenerator.begin();
    }
    void await_resume() {}


    void Update()
    {
        if (SleepIterator != SleepGenerator.end())
        {
            SleepIterator++;
        }
        else
        {
            Handle.resume();
        }
    }

private:
  
    float Duration = 0.f;
    std::coroutine_handle<Coroutine::promise_type> Handle;
    std::experimental::generator<bool>::iterator SleepIterator;
    std::experimental::generator<bool> SleepGenerator;

    std::experimental::generator<bool> SleepFor(
        std::chrono::nanoseconds duration
    ) {
        using namespace std::chrono;

        auto currentTime = steady_clock::now();
        const auto startTime = currentTime;
        const auto endTime = startTime + duration;
        while (currentTime < endTime) {
            co_yield false;
            currentTime = steady_clock::now();
        }
        co_yield true;
    }
};