#pragma once
#include <functional>
#include <coroutine>
#include "WaitSeconds.h"
#include "../Task.h"
#include "../CoroutineManager.h"
#include <functional>


class WaitBool
{
public:
	WaitBool(std::function<bool(void)>& InWaitExpression)
		:
		WaitExpression(InWaitExpression)
	{

	}
	
	bool await_ready() const noexcept { return WaitExpression(); }
    void await_suspend(std::coroutine_handle<Task::promise_type> InHandle)
	{
		CoroutineManager::Get().StartCoroutine(UpdateBoolCheck());
	}
    void await_resume() {}




private:
	std::function<bool(void)> WaitExpression;


	Task UpdateBoolCheck()
	{
		while (!WaitExpression())
		{
			co_await WaitSeconds(0.1f);
		}
		co_return;
	}

};