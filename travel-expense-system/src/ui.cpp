#include "ui.hpp"

std::string ui::readString()
{
    std::string string;
    std::cin >> string;
    return string;
}

Result<unsigned int> ui::readUint()
{
    unsigned input = 0;

    try
    {
        input = std::stoi(readString());
    }
    catch (const std::invalid_argument&)
    {
        writeError("Input in an incorrect format.");
        return Result<unsigned>::fail();
    }

    return Result<unsigned>::ok(input);
}

Result<double> ui::readUnsignedDouble()
{
    double input = 0;

    try
    {
        input = std::stoi(readString());
    }
    catch (const std::invalid_argument&)
    {
        writeError("Input in an incorrect format.");
        return Result<double>::fail();
    }

    if (input < 0.0)
    {
        writeError("Input must be greater than, or equal to, 0.0");
        return Result<double>::fail();
    }

    return Result<double>::ok(input);
}
