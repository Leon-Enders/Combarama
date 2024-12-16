#pragma once
#include <chrono>
#include <functional>
#include "Coroutine.h"
#include "SDL3/SDL_log.h"


class GameObject;

//Awaitable which suspends for the set Delay(in Seconds) on the main thread
class WaitSeconds
{
public:
    WaitSeconds(float InDuration, GameObject* InOwningGameObject) : Duration(InDuration), OwningGameObject(InOwningGameObject) {}
    ~WaitSeconds();
   
  
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<Coroutine::promise_type> InHandle);
    void await_resume() {}


    void Update();
private:
  
    float Duration = 0.f;
    GameObject* OwningGameObject = nullptr;
  
    std::coroutine_handle<Coroutine::promise_type> Handle;
    std::coroutine_handle<CoroutineSuspended::promise_type> SleeperHandle;


    CoroutineSuspended Sleep(std::chrono::nanoseconds Duration);
};