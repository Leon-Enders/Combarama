#include "WaitSeconds.h"
#include "../../Entity/Actor.h"

WaitSeconds::~WaitSeconds()
{
    OwningGameObject->RemoveAwaitable(*this);
}

void WaitSeconds::await_suspend(std::coroutine_handle<Coroutine::promise_type> InHandle)
{
    // Cache Owned Handle
    Handle = InHandle;
    auto DurationNS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(Duration));

    auto SleepCoroutine = Sleep(DurationNS);
    SleeperHandle = SleepCoroutine.Handle;

    // Add to Awaitable list of the owning actor
    OwningGameObject->AddAwaitable(*this);
}

void WaitSeconds::Update()
{
    if (!SleeperHandle.done())
    {
        SleeperHandle.resume();
    }
    else
    {
        Handle.resume();
    }
}

CoroutineSuspended WaitSeconds::Sleep(std::chrono::nanoseconds Duration)
{
    using namespace std::chrono;
    
    auto currentTime = steady_clock::now();
    const auto startTime = currentTime;
    const auto endTime = startTime + Duration;
    while (currentTime < endTime)
    {
        co_await std::suspend_always();
        currentTime = steady_clock::now();
    }
}