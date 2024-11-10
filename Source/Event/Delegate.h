#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <algorithm>
#include <ranges>
#include <type_traits>


// Each Delegate class has an option to bind an anonymous function,
// when doing so the function has to be manually undbound
template<typename R, typename T>
class Delegate
{
public:
    ~Delegate() {}

    
    void BindFunction(const std::function<R(T)>& FunctionToBind)
    {
        BoundFunction = FunctionToBind;
    }

   
    template <typename ObjType>
    void BindMemberFunction(std::shared_ptr<ObjType> Instance, R(ObjType::* MemberFunction)(T))
    {
        BoundFunction = [wInstance = std::weak_ptr<ObjType>(Instance), MemberFunction](T arg)-> R
            {
                if (auto sInstance = wInstance.lock())
                {
                    return (sInstance.get()->*MemberFunction)(arg);
                }

                return R();
            };
    }

    
    void Clear()
    {
        BoundFunction = std::function<R(T)>();
    }

    
    template<typename Ret = R>
    typename std::enable_if<!std::is_void<Ret>::value, Ret>::type
    Invoke(T arg)
    {
        try
        {
            if (BoundFunction)
            {
                return BoundFunction(arg);
            }
            else
            {
                BoundFunction = std::function<R(T)>();
            }
            
        }
        catch (...)
        {
            BoundFunction = std::function<R(T)>();
        } 

        return R();
    }

    
    template<typename Ret = R>
    typename std::enable_if<std::is_void<Ret>::value, void>::type
    Invoke(T arg)
    {
        try
        {
            if (BoundFunction)
            {
                BoundFunction(arg);
            }
            else
            {
                BoundFunction = std::function<R(T)>();
            }
        }
        catch (...)
        {
            BoundFunction = std::function<R(T)>();
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

    
    void BindFunction(const std::function<R()>& FunctionToBind)
    {
        BoundFunction = FunctionToBind;
    }


    template <typename ObjType>
    void BindMemberFunction(std::shared_ptr<ObjType> Instance, R(ObjType::* MemberFunction)())
    {
        BoundFunction = [wInstance = std::weak_ptr<ObjType>(Instance), MemberFunction]()-> R
            {
                if (auto sInstance = wInstance.lock())
                {
                    return (sInstance.get()->*MemberFunction)();
                }

                return R();
            };
    }

   
    void Clear()
    {
        BoundFunction = std::function<R()>(); 
    }

   
    template<typename Ret = R>
    typename std::enable_if<!std::is_void<Ret>::value, Ret>::type
    Invoke()
    {
        try
        {
            if (BoundFunction)
            {
                return BoundFunction();
            }
            else
            {
                BoundFunction = std::function<R()>();
            }
        }
        catch (...)
        {
            BoundFunction = std::function<R()>();
        }
        return R();
    }

    template<typename Ret = R>
    typename std::enable_if<std::is_void<Ret>::value, void>::type
    Invoke()
    {
        try
        {
            if (BoundFunction)
            {
                BoundFunction();
            }
            else
            {
                BoundFunction = std::function<R()>();
            }
        }
        catch (...)
        {
            BoundFunction = std::function<R()>();
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
        BoundFunctions.emplace_back(
            [wInstance = std::weak_ptr<ObjType>(Instance), MemberFunction](T arg)-> R
            {
                if (auto sInstance = wInstance.lock())
                {
                    return (sInstance.get()->*MemberFunction)(arg);
                }

                return R();
            });
    }

    void UnSubscribe(const std::function<R(T)>& FunctionToRemove)
    {
       std::erase_if(BoundFunctions,
            [&](const std::function<R(T)>& BoundFunction)
            {
                return BoundFunction.target_type() == FunctionToRemove.target_type();
            });
    }

    
    template<typename Ret = R>
    typename std::enable_if<!std::is_void<Ret>::value, std::vector<Ret>>::type
    Broadcast(T arg) 
    {
        std::vector<Ret> Results;
        for (auto it = BoundFunctions.begin(); it != BoundFunctions.end(); ) 
        {
            try 
            {
                if (*it) 
                {
                    Results.push_back((*it)(arg));
                    if (BoundFunctions.size() == 0)
                    {
                        return;
                    }
                    ++it;
                }
                else 
                {
                    it = BoundFunctions.erase(it);
                }
            }
            catch (...) 
            {
                it = BoundFunctions.erase(it);
            }
        }
        return Results;
    }

    
    template<typename Ret = R>
    typename std::enable_if<std::is_void<Ret>::value, void>::type
    Broadcast(T arg) 
    {
        for (auto it = BoundFunctions.begin(); it != BoundFunctions.end(); ) 
        {
            try 
            {
                if (*it) 
                {
                    (*it)(arg);
                    if (BoundFunctions.size() == 0)
                    {
                        return;
                    }
                    ++it;
                }
                else 
                {
                    it = BoundFunctions.erase(it);
                }
            }
            catch (...) 
            {
                it = BoundFunctions.erase(it);
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
    void AddMemberFunction(std::shared_ptr<ObjType> Instance, R(ObjType::* MemberFunction)())
    {
        BoundFunctions.emplace_back([wInstance = std::weak_ptr<ObjType>(Instance), MemberFunction]() -> R {
            if (auto sInstance = wInstance.lock()) {
                return (sInstance.get()->*MemberFunction)();
            }
            return R();
            });
    }

  
   
    void UnSubscribe(const std::function<R()>& FunctionToRemove)
    {
        std::erase_if(BoundFunctions,
            [&](const std::function<R()>& BoundFunction)
            {
                return BoundFunction.target_type() == FunctionToRemove.target_type();
            });
    }

    
    
    template<typename Ret = R>
    typename std::enable_if<!std::is_void<Ret>::value, std::vector<Ret>>::type
    Broadcast() 
    {
        std::vector<Ret> Results;
        for (auto it = BoundFunctions.begin(); it != BoundFunctions.end(); ) 
        {
            try 
            {
                if (*it) 
                {
                    Results.push_back((*it)());
                    if (BoundFunctions.size() == 0)
                    {
                        return;
                    }
                    ++it;
                }
                else 
                {
                    it = BoundFunctions.erase(it);
                }
            }
            catch (...) 
            {
                it = BoundFunctions.erase(it);
            }
        }
        return Results;
    }

   
    
    template<typename Ret = R>
    typename std::enable_if<std::is_void<Ret>::value, void>::type
    Broadcast() 
    {
        for (auto it = BoundFunctions.begin(); it != BoundFunctions.end(); ) 
        {
            try 
            {
                if (*it) 
                {
                    (*it)();
                    if (BoundFunctions.size() == 0)
                    {
                        return;
                    }
                    ++it;
                }
                else 
                {
                    it = BoundFunctions.erase(it);
                }
            }
            catch (...) 
            {
                it = BoundFunctions.erase(it);
            }
        }
    }

private:
    std::vector<std::function<R()>> BoundFunctions;
};