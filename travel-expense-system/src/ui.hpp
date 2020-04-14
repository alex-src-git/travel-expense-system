#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include "result.hpp"

namespace ui
{
    template <typename T> void write(T message);
    template <typename T> void writeLine(T message);
    template <typename T> void writeHeading(T message);
    template <typename T> void writeError(T message);

    // TODO: Rename?
    template <typename T> T readRecursive(const std::string& prompt, std::function<Result<T>()> read);
    std::string readString();
    Result<unsigned int> readUint();
    Result<double> readUnsignedDouble();
    Result<bool> readBool();
    Result<unsigned int> switchMenu(const std::vector<std::string>& options);

    enum class Colour
    {
        White,
        Red
    };

    void setTextColour(Colour colour);

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
    void writeHeading(T message)
    {
        std::cout << std::endl << message << std::endl;
    }

    template <typename T>
    void writeError(T message)
    {
        setTextColour(ui::Colour::Red);
        std::cout << "Error: " << message << std::endl;
        setTextColour(ui::Colour::White);
    }

    template<typename T>
    T readRecursive(const std::string& prompt, std::function<Result<T>()> read)
    {
        while (true)
        {
            writeHeading(prompt);

            Result<T> input = read();
            if (input)
            {
                return input.value;
            }
        }
    }

    #pragma endregion
}
