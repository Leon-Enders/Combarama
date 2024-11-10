#pragma once
#include <iostream>
#include <coroutine>

struct Task
{
    struct promise_type
    {
        Task get_return_object() { return Task{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };

    explicit Task(std::coroutine_handle<promise_type> InHandle) : Handle(InHandle) {}
    ~Task()
    {
        if (Handle) Handle.destroy();
    }

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    Task(Task&& Other) noexcept
        : 
        Handle(Other.Handle)
    { 
        Other.Handle = {};
    }
    Task& operator=(Task&& t) noexcept 
    {
        if (this == &t) return *this;
        if (Handle) Handle.destroy();
        Handle = t.Handle;
        t.Handle = {};
        return *this;
    }
   
    void Resume() { Handle.resume(); }
    bool IsDone() { return Handle.done(); }

    std::coroutine_handle<promise_type> Handle;
};