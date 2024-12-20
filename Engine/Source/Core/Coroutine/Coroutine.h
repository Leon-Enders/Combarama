#pragma once
#include <iostream>
#include <coroutine>

struct Coroutine
{
    struct promise_type
    {
        Coroutine get_return_object() { return Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };

    explicit Coroutine(std::coroutine_handle<promise_type> InHandle) : Handle(InHandle) {}
   

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
   

    std::coroutine_handle<promise_type> Handle;
};




struct CoroutineSuspended
{
    struct promise_type
    {
        CoroutineSuspended get_return_object() { return CoroutineSuspended{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };

    explicit CoroutineSuspended(std::coroutine_handle<promise_type> InHandle) : Handle(InHandle) {}


    CoroutineSuspended(const CoroutineSuspended&) = delete;
    CoroutineSuspended& operator=(const CoroutineSuspended&) = delete;
    CoroutineSuspended(CoroutineSuspended&& Other) noexcept
        :
        Handle(Other.Handle)
    {
        Other.Handle = {};
    }
    CoroutineSuspended& operator=(CoroutineSuspended&& t) noexcept
    {
        if (this == &t) return *this;
        if (Handle) Handle.destroy();
        Handle = t.Handle;
        t.Handle = {};
        return *this;
    }


    std::coroutine_handle<promise_type> Handle;
};