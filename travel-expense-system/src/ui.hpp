#pragma once
#include <iostream>
#include <functional>
#include <string>
#include "result.hpp"

namespace ui
{
    template <typename T> void write(T message);
    template <typename T> void writeLine(T message);
    template <typename T> void writeError(T message);

    // TODO: Rename?
    template <typename T> Result<T> readRecursive(const std::string& prompt, std::function<Result<T>> read);
    std::string readString();
    Result<unsigned int> readUint();
    Result<double> readUnsignedDouble();

    #pragma region Template Function Definitions

    template <typename T>
    void write(T message)
    {
        std::cout << message;
    }

    template <typename T>
    void writeLine(T message)
    {
        std::cout << message << std::endl;
    }

    template <typename T>
    void writeError(T message)
    {
        std::cout << "Error: " << message << std::endl;
    }

    template<typename T>
    Result<T> readRecursive(const std::string& prompt, std::function<Result<T>> read)
    {
        while (true)
        {
            writeLine(prompt);

            Result<T> input = read();
            if (input)
            {
                return input.value;
            }
        }
    }

    #pragma endregion
}
