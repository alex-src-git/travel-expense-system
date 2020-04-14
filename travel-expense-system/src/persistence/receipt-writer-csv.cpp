#include "receipt-writer-csv.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace persistence;
namespace fs = std::filesystem;

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
    std::string name = std::to_string(receipt.getId());
    return directory + name + ".csv";
}

std::string ReceiptWriterCsv::toCsv(const Receipt& receipt)
{
    std::stringstream ss;
    const ReceiptConfig& receiptConfig = receipt.getConfig();
    
    // TODO: Reorder...
    ss << receipt.getId() << ',';
    ss << receipt.getTimeCreated() << ',';
    ss << receiptConfig.getCurrency() << ',';
    ss << receiptConfig.getPctLiableEmployeeTravel() << ',';
    ss << receiptConfig.getPctLiableEmployeeExpenses() << ',';
    ss << receiptConfig.getPayFreeBandEmployeeTravel() << ',';
    ss << receiptConfig.getPayFreeBandEmployeeExpenses() << ',';
    ss << receipt.getExpensesCost() << ',';
    ss << receipt.getTravelCost() << ',';

    return ss.str();
}

void ReceiptWriterCsv::writeToFile(const std::string& fileName, const std::string& content)
{
    std::ofstream file(fileName);
    file << content;
    file.close();
}
