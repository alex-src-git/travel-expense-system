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
        input = std::stod(readString());
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

Result<unsigned int> ui::switchMenu(const std::vector<std::string>& options)
{
    for (std::size_t i = 0; i < options.size(); i++)
    {
        write(std::to_string(i + 1) + ": ");
        writeLine(options[i]);
    }

    Result<unsigned int> input = readUint();
    input.value -= 1;

    if (input && input.value >= options.size())
    {
        writeError("Input out of range.");
        input = Result<unsigned int>::fail();
    }

    return input;
}
