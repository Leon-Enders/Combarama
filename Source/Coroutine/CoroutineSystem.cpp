#include "CoroutineSystem.h"


CoroutineSystem CoroutineSystem::Instance;

void CoroutineSystem::Tick(float DeltaTime)
{

    for (auto it = Coroutines.begin(); it != Coroutines.end();)
    {
        auto& [Handle, RemainingTime] = *it;
        RemainingTime -= DeltaTime;
    

        if (RemainingTime <= 0)
        {
            Handle.resume();
            it = Coroutines.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
}
