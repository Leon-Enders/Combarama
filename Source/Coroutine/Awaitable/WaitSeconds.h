#pragma once
#include <chrono>
#include <functional>
#include <experimental/generator>
#include "../Coroutine.h"
#include "SDL3/SDL_log.h"


class Actor;

//Awaitable which suspends for the set Delay(in Seconds) on the main thread
class WaitSeconds
{
public:
    WaitSeconds(float InDuration, Actor* InOwningActor) : Duration(InDuration), OwningActor(InOwningActor) {}
    ~WaitSeconds();
   
  
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<Coroutine::promise_type> InHandle);
    void await_resume() {}


    void Update();
private:
  
    float Duration = 0.f;
    Actor* OwningActor = nullptr;
  
    std::coroutine_handle<Coroutine::promise_type> Handle;

    std::experimental::generator<bool>::iterator SleepIterator;
    std::experimental::generator<bool> SleepGenerator;
    std::experimental::generator<bool> SleepFor(std::chrono::nanoseconds Duration);
  
};