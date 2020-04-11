#pragma once

template <typename T> 
struct Result final
{
    bool isOk;
    T value;

    static constexpr Result<T> ok(T value)
    {
        return Result<T>{true, value};
    }

    static constexpr Result<T> fail()
    {
        return Result<T>{false, {}};
    }

    operator bool() const
    {
        return isOk;
    }
};
