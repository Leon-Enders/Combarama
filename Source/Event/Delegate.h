#pragma once
#include <functional>
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
    void AddMemberFunction(ObjType* Instance, R(ObjType::* MemberFunction)(T))
    {
        BoundFunctions.push_back([=](T arg) { return (Instance->*MemberFunction)(arg); });
    }

    // Remove function based on function equality
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
        for (const auto& Binding : BoundFunctions)
        {
            if (Binding) {
                Results.push_back(Binding(arg));
            }
        }
        return Results;
    }

    
    template<typename Ret = R>
    typename std::enable_if<std::is_void<Ret>::value, void>::type
        Broadcast(T arg)
    {
        for (const auto& Binding : BoundFunctions)
        {
            if (Binding)
            {
                Binding(arg);
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


    template <typename ObjType>
    void AddMemberFunction(ObjType*Instance, R(ObjType::* MemberFunction)()) 
    {
        BoundFunctions.push_back([=]() { return (Instance->*MemberFunction)(); });
    }

  
    void UnSubscribe(const std::function<R()>& FunctionToRemove)
    {
        BoundFunctions.erase(std::remove_if(BoundFunctions.begin(), BoundFunctions.end(),
            [&](const std::function<R()>& BoundFunction)
            {
                return BoundFunction.target_type() == FunctionToRemove.target_type();
            }), BoundFunctions.end());
    }

    
    template<typename Ret = R>
    typename std::enable_if<!std::is_void<Ret>::value, std::vector<Ret>>::type
        Broadcast() {
        std::vector<Ret> Results;
        for (const auto& Binding : BoundFunctions)
        {
            if (Binding) {
                Results.push_back(Binding());
            }
        }
        return Results;
    }

   
    template<typename Ret = R>
    typename std::enable_if<std::is_void<Ret>::value, void>::type
        Broadcast() {
        for (const auto& Binding : BoundFunctions)
        {
            if (Binding) {
                Binding();
            }
        }
    }

private:
    std::vector<std::function<R()>> BoundFunctions;
};