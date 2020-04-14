#pragma once
#include <vector>
#include <memory>
#include <string>

#include "../receipt.hpp"
#include "../receipt-config.hpp"

namespace persistence
{
    class ReceiptReaderCsv final 
    {
    public:
        ReceiptReaderCsv();

        std::unique_ptr<Receipt> load(const std::string& name);
        std::vector<std::unique_ptr<Receipt>> loadAll();

    private:
        static std::string getFileContent(const std::string& fileName);
        static void replaceNewlinesWithCommas(std::string& string);
        static std::vector<std::string> splitOnComma(const std::string& string);
        static std::vector<std::string> readTokens(const std::string& fileName);

        static void ensureThatDirectoryExists(const std::string& name);
        static std::unique_ptr<ReceiptConfig> readConfig(const std::vector<std::string>& tokens);
        static std::unique_ptr<Receipt> readReceipt(const std::vector<std::string>& tokens,
            std::unique_ptr<ReceiptConfig> cfg);
    };
}
