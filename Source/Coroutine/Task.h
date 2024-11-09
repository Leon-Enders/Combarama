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
        void unhandled_exception() { std::terminate(); }
    };

    explicit Task(std::coroutine_handle<promise_type> InHandle) : Handle(InHandle) {}
    ~Task()
    {
        if (Handle) Handle.destroy();
    }
    std::coroutine_handle<promise_type> Handle;
};