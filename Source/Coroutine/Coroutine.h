#pragma once
#include <iostream>
#include <coroutine>

struct Coroutine
{
    struct promise_type
    {
        Coroutine get_return_object() { return Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };

    explicit Coroutine(std::coroutine_handle<promise_type> InHandle) : Handle(InHandle) {}
    ~Coroutine()
    {
        if (Handle) Handle.destroy();
    }

    Coroutine(const Coroutine&) = delete;
    Coroutine& operator=(const Coroutine&) = delete;
    Coroutine(Coroutine&& Other) noexcept
        : 
        Handle(Other.Handle)
    { 
        Other.Handle = {};
    }
    Coroutine& operator=(Coroutine&& t) noexcept
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