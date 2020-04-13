#include "receipt-reader-csv.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <filesystem>

using namespace persistence;
namespace fs = std::filesystem;

std::unique_ptr<Receipt> ReceiptReaderCsv::load(const std::string& fileName)
{
    std::vector<std::string> tokens = readTokens(fileName);
    std::unique_ptr<ReceiptConfig> cfg = readConfig(tokens);
    std::unique_ptr<Receipt> receipt = readReceipt(tokens, std::move(cfg));
    
    return receipt;
}

std::vector<std::unique_ptr<Receipt>> ReceiptReaderCsv::loadAll()
{
    std::vector<std::unique_ptr<Receipt>> receipts;

    for (const auto& entry : fs::directory_iterator(""))
    {
        const fs::path path = entry.path();
        if (path.extension() == ".csv")
        {
            std::unique_ptr<Receipt> receipt = load(path.string());
            receipts.push_back(std::move(receipt));
        }
    }

    return receipts;
}

std::string ReceiptReaderCsv::getFileContent(const std::string& name)
{
    std::ifstream file(name);
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void ReceiptReaderCsv::replaceNewlinesWithCommas(std::string& string)
{
    std::replace(string.begin(), string.end(), '\n', ',');
}

std::vector<std::string> ReceiptReaderCsv::splitOnComma(const std::string& string)
{
    std::stringstream s(string);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(s, token, ','))
    {
        tokens.push_back(token);
    }

     return tokens;
}

std::vector<std::string> persistence::ReceiptReaderCsv::readTokens(const std::string& fileName)
{
    std::string content = getFileContent(fileName);
    replaceNewlinesWithCommas(content);
    std::vector<std::string> tokens = splitOnComma(content);
    
    // HACK: Potentially hefty copy operation.
    return tokens;
}

std::unique_ptr<ReceiptConfig> ReceiptReaderCsv::readConfig(const std::vector<std::string>& tokens)
{
    // WARNING WARNING WARNING
    // HACK: Very unsafe...
    // I would use a format like json, via a library, if this was production code.
    // WARNING WARNING WARNING

    static constexpr char* scanToEndOfString = "%s";
    char currency[256];
    std::sscanf(tokens[2].c_str(), "%[^\n]", &currency);


    double pctLiableEmployeeTravel;
    std::sscanf(tokens[3].c_str(), "%lf", &pctLiableEmployeeTravel);

    double pctLiableEmployeeExpenses;
    std::sscanf(tokens[4].c_str(), "%lf", &pctLiableEmployeeExpenses);

    double payFreeBandEmployeeTravel;
    std::sscanf(tokens[5].c_str(), "%lf", &payFreeBandEmployeeTravel);

    double payFreeBandEmployeeExpenses;
    std::sscanf(tokens[6].c_str(), "%lf", &payFreeBandEmployeeExpenses);

    return std::make_unique<ReceiptConfig>(
        std::string(currency),
        pctLiableEmployeeTravel,
        pctLiableEmployeeExpenses, payFreeBandEmployeeTravel,
        payFreeBandEmployeeExpenses);
}

std::unique_ptr<Receipt> ReceiptReaderCsv::readReceipt(const std::vector<std::string>& tokens, 
    std::unique_ptr<ReceiptConfig> cfg)
{
    // WARNING WARNING WARNING
    // HACK: Very unsafe...
    // I would use a format like json, via a library, if this was production code.
    // WARNING WARNING WARNING

    std::size_t id;
    std::sscanf(tokens[0].c_str(), "%zu", &id);

    std::time_t timeCreated;
    std::sscanf(tokens[1].c_str(), "%lld", &timeCreated);

    // ReceiptConfig's members occupy tokens [2..6]
    // It should probably be serialised separately, think: the "Flyweight Pattern".

    double expenses;
    std::sscanf(tokens[7].c_str(), "%lf", &expenses);

    double travel;
    std::sscanf(tokens[8].c_str(), "%lf", &travel);

    return std::make_unique<Receipt>(
        id,
        timeCreated,
        *cfg,
        expenses,
        travel);
}
