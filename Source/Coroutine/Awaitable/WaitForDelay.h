#pragma once
#include <chrono>
#include <SDL3/SDL_timer.h>
#include "../Task.h"



class WaitSeconds
{
private:
    float TimeRemaining;
    std::coroutine_handle<Task::promise_type> Handle;

public:
    WaitSeconds(float Time) : TimeRemaining(Time) {}

    void await_resume() {}
    bool await_ready() { return TimeRemaining <= 0.f; }
    void await_suspend(std::coroutine_handle<Task::promise_type> InHandle)
    {
        Handle = InHandle;
        //TODO Here a callback should be added which gets called by another object which gets updated in the game loop.
        // each update checks if the TimeRemaining is less then 0
        // if it is the Handle resumes
    }
};