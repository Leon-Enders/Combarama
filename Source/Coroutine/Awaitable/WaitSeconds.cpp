#include "WaitSeconds.h"
#include "../../Entity/Actor.h"

WaitSeconds::~WaitSeconds()
{
    OwningActor->RemoveAwaitable(*this);
}

void WaitSeconds::await_suspend(std::coroutine_handle<Coroutine::promise_type> InHandle)
{
    // Cache Owned Handle
    Handle = InHandle;
    auto DurationNS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(Duration));

    SleepGenerator = SleepFor(DurationNS);
    SleepIterator = SleepGenerator.begin();

    // Add to Awaitable list of the owning actor
    OwningActor->AddAwaitable(*this);

}

void WaitSeconds::Update()
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

std::experimental::generator<bool> WaitSeconds::SleepFor(std::chrono::nanoseconds Duration)
{
    using namespace std::chrono;

    auto currentTime = steady_clock::now();
    const auto startTime = currentTime;
    const auto endTime = startTime + Duration;
    while (currentTime < endTime) 
    {
        co_yield false;
        currentTime = steady_clock::now();
    }
    co_yield true;
}
