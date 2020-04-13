#pragma once
#include "../receipt.hpp"
#include <string>

namespace persistence
{
    class ReceiptWriterCsv final
    {
    public:
        void save(const Receipt& receipt);

    private:
        static std::string makeFileName(const Receipt& receipt);
        static std::string toCsv(const Receipt& receipt);
        static void writeToFile(const std::string& fileName, const std::string& content);
    };
}
