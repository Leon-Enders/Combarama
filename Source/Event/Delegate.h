#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <algorithm>
#include <type_traits>



template<typename R, typename T>
class Delegate
{
public:
    ~Delegate() {}

    
    void Bind(const std::function<R(T)>& FunctionToBind)
    {
        BoundFunction = FunctionToBind;
    }

   
    template <typename ObjType>
    void BindMemberFunction(ObjType* Instance, R(ObjType::* MemberFunction)(T))
    {
        BoundFunction = [=](T arg) { return (Instance->*MemberFunction)(arg); };
    }

    
    void Remove()
    {
        BoundFunction = std::function<R(T)>();
    }

    
    template<typename Ret = R>
    typename std::enable_if<!std::is_void<Ret>::value, Ret>::type
        Invoke(T arg)
    {
        if (BoundFunction)
        {
            return BoundFunction(arg);
        }
        return R(); 
    }

    
    template<typename Ret = R>
    typename std::enable_if<std::is_void<Ret>::value, void>::type
        Invoke(T arg)
    {
        if (BoundFunction)
        {
            BoundFunction(arg);
        }
    }

private:
    std::function<R(T)> BoundFunction;
};


template<typename R>
class Delegate<R, void>
{
public:
    ~Delegate() {}

    
    void Bind(const std::function<R()>& FunctionToBind)
    {
        BoundFunction = FunctionToBind;
    }


    template <typename ObjType>
    void BindMemberFunction(ObjType* Instance, R(ObjType::* MemberFunction)())
    {
        BoundFunction = [=]() { return (Instance->*MemberFunction)(); };
    }

   
    void Remove()
    {
        BoundFunction = std::function<R()>(); 
    }

   
    template<typename Ret = R>
    typename std::enable_if<!std::is_void<Ret>::value, Ret>::type
        Invoke()
    {
        if (BoundFunction)
        {
            return BoundFunction();
        }
        return R();
    }

    template<typename Ret = R>
    typename std::enable_if<std::is_void<Ret>::value, void>::type
        Invoke()
    {
        if (BoundFunction)
        {
            BoundFunction();
        }
    }

private:
    std::function<R()> BoundFunction;
};


template<typename R, typename T>
class MulticastDelegate
{
public:
    ~MulticastDelegate() {}

   
    void AddFunction(const std::function<R(T)>& FunctionToBind)
    {
        BoundFunctions.push_back(FunctionToBind);
    }

   
    template <typename ObjType>
    void AddMemberFunction(std::shared_ptr<ObjType> Instance, R(ObjType::* MemberFunction)(T))
    {
        BoundFunctions.emplace_back([wInstance = std::weak_ptr<ObjType>(Instance), MemberFunction](T arg) -> R {
            if (auto sInstance = wInstance.lock()) {
                return (sInstance.get()->*MemberFunction)(arg);
            }
            return R(); // Return default if instance is destroyed
            });
    }

    void UnSubscribe(const std::function<R(T)>& FunctionToRemove)
    {
        BoundFunctions.erase(std::remove_if(BoundFunctions.begin(), BoundFunctions.end(),
            [&](const std::function<R(T)>& BoundFunction)
            {
                return BoundFunction.target_type() == FunctionToRemove.target_type();
            }), BoundFunctions.end());
    }

    
    template<typename Ret = R>
    typename std::enable_if<!std::is_void<Ret>::value, std::vector<Ret>>::type
        Broadcast(T arg) {
        std::vector<Ret> Results;
        for (auto it = BoundFunctions.begin(); it != BoundFunctions.end(); ) {
            try {
                if (*it) {
                    Results.push_back((*it)(arg));
                    ++it;
                }
                else {
                    it = BoundFunctions.erase(it);
                }
            }
            catch (...) {
                it = BoundFunctions.erase(it);
            }
        }
        return Results;
    }

    
    template<typename Ret = R>
    typename std::enable_if<std::is_void<Ret>::value, void>::type
        Broadcast(T arg) {
        for (auto it = BoundFunctions.begin(); it != BoundFunctions.end(); ) {
            try {
                if (*it) {
                    (*it)(arg);
                    ++it;
                }
                else {
                    it = BoundFunctions.erase(it); // Remove expired functions
                }
            }
            catch (...) {
                it = BoundFunctions.erase(it); // Handle any failures gracefully
            }
        }
    }

private:
    std::vector<std::function<R(T)>> BoundFunctions;
};


template<typename R>
class MulticastDelegate<R, void>
{
public:
    ~MulticastDelegate() {}


    void AddFunction(const std::function<R()>& FunctionToBind)
    {
        BoundFunctions.push_back(FunctionToBind);
    }


    // Add a member function with a weak reference to the instance
    template <typename ObjType>
    void AddMemberFunction(std::shared_ptr<ObjType> Instance, R(ObjType::* MemberFunction)())
    {
        BoundFunctions.emplace_back([wInstance = std::weak_ptr<ObjType>(Instance), MemberFunction]() -> R {
            if (auto sInstance = wInstance.lock()) {
                return (sInstance.get()->*MemberFunction)();
            }
            return R(); // Return default if instance is destroyed (for non-void R)
            });
    }

  
    // Unsubscribe a specific function (using equality)
    void UnSubscribe(const std::function<R()>& FunctionToRemove)
    {
        BoundFunctions.erase(std::remove_if(BoundFunctions.begin(), BoundFunctions.end(),
            [&](const std::function<R()>& BoundFunction)
            {
                return BoundFunction.target_type() == FunctionToRemove.target_type();
            }), BoundFunctions.end());
    }

    
    // Broadcast for non-void return type, removing expired functions as it goes
    template<typename Ret = R>
    typename std::enable_if<!std::is_void<Ret>::value, std::vector<Ret>>::type
        Broadcast() {
        std::vector<Ret> Results;
        for (auto it = BoundFunctions.begin(); it != BoundFunctions.end(); ) {
            try {
                if (*it) {
                    Results.push_back((*it)());
                    ++it;
                }
                else {
                    it = BoundFunctions.erase(it); // Remove expired functions
                }
            }
            catch (...) {
                it = BoundFunctions.erase(it); // Handle any failures gracefully
            }
        }
        return Results;
    }

   
    // Broadcast for void return type, removing expired functions as it goes
    template<typename Ret = R>
    typename std::enable_if<std::is_void<Ret>::value, void>::type
        Broadcast() {
        for (auto it = BoundFunctions.begin(); it != BoundFunctions.end(); ) {
            try {
                if (*it) {
                    (*it)();
                    ++it;
                }
                else {
                    it = BoundFunctions.erase(it); // Remove expired functions
                }
            }
            catch (...) {
                it = BoundFunctions.erase(it); // Handle any failures gracefully
            }
        }
    }

private:
    std::vector<std::function<R()>> BoundFunctions;
};