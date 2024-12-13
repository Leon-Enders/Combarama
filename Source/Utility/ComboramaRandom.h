#pragma once
#include <random>


struct RandomGenerator
{
    static std::mt19937& GetRandomEngine()
    {
        static std::mt19937 engine(static_cast<unsigned int>(std::time(nullptr)));
        return engine;
    }
};