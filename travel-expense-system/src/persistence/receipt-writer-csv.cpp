#include "receipt-writer-csv.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace persistence;
namespace fs = std::filesystem;

static std::string hexFormat(std::size_t value)
{
    std::stringstream ss;
    ss << std::hex << value;
    return ss.str();
}

void ReceiptWriterCsv::save(const Receipt& receipt)
{
    std::string fileName = makeFileName(receipt);
    std::string csv = toCsv(receipt);
    writeToFile(fileName, csv);
}

std::string ReceiptWriterCsv::makeFileName(const Receipt& receipt)
{
    std::string directory = "receipts\\";
    fs::create_directory(directory);
    std::string name = hexFormat(receipt.getId());
    return directory + name + ".csv";
}

std::string ReceiptWriterCsv::toCsv(const Receipt& receipt)
{
    std::stringstream ss;
    const ReceiptConfig& receiptConfig = receipt.getConfig();
    
    // TODO: Reorder...
    ss << receipt.getId() << ',';
    ss << receipt.getTimeCreated() << ',';
    ss << receipt.getExpensesCost() << ',';
    ss << receipt.getTravelCost() << ',';
    ss << receiptConfig.getCurrency() << ',';
    ss << receiptConfig.getPctLiableEmployeeTravel() << ',';
    ss << receiptConfig.getPctLiableEmployeeExpenses() << ',';
    ss << receiptConfig.getPayFreeBandEmployeeTravel() << ',';
    ss << receiptConfig.getPayFreeBandEmployeeExpenses() << ',';

    return ss.str();
}

void ReceiptWriterCsv::writeToFile(const std::string& fileName, const std::string& content)
{
    std::ofstream file(fileName);
    file << content;
    file.close();
}
