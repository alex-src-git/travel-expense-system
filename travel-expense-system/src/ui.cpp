#include "ui.hpp"

#ifdef _WIN32
    // We need to use Windows platform code to change text colour.
    #include <windows.h>
#endif

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

Result<bool> ui::readBool()
{
    std::string line = readString();
    char firstChar = std::tolower(line[0]);
    if (line.length() != 1 || !(firstChar == 'y' || firstChar == 'n'))
    {
        writeError("Input must be either y or n.");
        return Result<bool>::fail();
    }

    return Result<bool>::ok(firstChar == 'y');
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

void ui::setTextColour(Colour colour)
{
    // The changing of console text colour is only supported on Windows.
    // No-op on other operating systems.
    #if _WIN32

    unsigned short win32ColourFlag = 0;

    switch (colour)
    {
        case Colour::White:
            win32ColourFlag = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;

        case Colour::Red:
            win32ColourFlag = FOREGROUND_RED;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        win32ColourFlag);

    #endif
}
