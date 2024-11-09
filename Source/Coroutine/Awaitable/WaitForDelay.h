#pragma once
#include <coroutine>
#include <chrono>

class WaitForDelay
{
public:
    explicit WaitForDelay(std::chrono::milliseconds InDuration)
        : Duration(InDuration), StartTime(std::chrono::steady_clock::now()) {}

    
    bool await_ready() const noexcept
    {
        return std::chrono::steady_clock::now() >= StartTime + Duration;
    }

  
    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
       
    }

   
    void await_resume() const noexcept {}

private:
    std::chrono::milliseconds Duration;
    std::chrono::steady_clock::time_point StartTime;
};