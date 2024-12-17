#include "Transaction.h"

// Default constructor: initializes a blank transaction
Transaction::Transaction()
{
    ID = -1;                    // Invalid ID
    description = "";           // Blank description
    type = TransactionType::NONE; // Default transaction type
    amount = 0.0;               // Zero amount
    envelope = "blank";         // Default envelope name
    source = "";                // Empty source
}

// Constructor: initializes a transaction without a source field
Transaction::Transaction(int id, const std::string& desc, TransactionType t, double amt,
    const std::string& env, const std::chrono::system_clock::time_point& date)
    : ID(id), description(desc), type(t), amount(amt), envelope(env), date(date), source("") {}

// Constructor: initializes a transaction with all details, including source
Transaction::Transaction(int id, const std::string& desc, TransactionType t, double amt,
    const std::string& env, const std::chrono::system_clock::time_point& date, std::string source)
    : ID(id), description(desc), type(t), amount(amt), envelope(env), date(date), source(source) {}

// Getter for transaction ID
int Transaction::getId() const
{
    return ID;
}

// Getter for transaction description
std::string Transaction::getDescription() const
{
    return description;
}

// Getter for the associated envelope name
std::string Transaction::getEnvelope() const
{
    return envelope;
}

// Getter for transaction type
TransactionType Transaction::getType() const
{
    return type;
}

// Getter for transaction amount
double Transaction::getAmount() const
{
    return amount;
}

// Getter for transaction source
std::string Transaction::getSource() const
{
    return source;
}

// Getter for transaction date
std::chrono::system_clock::time_point Transaction::getDate() const
{
    return date;
}

// Returns the transaction date as a formatted string (e.g., "2024-06-18")
std::string Transaction::getDateAsString() const
{
    return formatDate(date); // Calls private formatDate helper
}

// Sets the transaction date by parsing a string
void Transaction::setDateFromString(const std::string& dateStr)
{
    date = parseDate(dateStr);
}

// Static method to parse a date string (e.g., "2024-06-18") into a time_point
std::chrono::system_clock::time_point Transaction::parseDate(const std::string& dateStr)
{
    std::istringstream ss(dateStr);
    std::tm tm = {};
    ss >> std::get_time(&tm, "%Y-%m-%d"); // Parse string into tm struct

    if (ss.fail()) {
        throw std::runtime_error("Failed to parse date: " + dateStr);
    }

    // Convert tm to time_point
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

// Formats a time_point into a string (e.g., "2024-06-18")
std::string Transaction::formatDate(const std::chrono::system_clock::time_point& tp) const
{
    auto timeT = std::chrono::system_clock::to_time_t(tp); // Convert to time_t
    std::tm localTime = {};
    localtime_s(&localTime, &timeT); // Safe version of localtime

    // Format time as "YYYY-MM-DD"
    std::ostringstream ss;
    ss << std::put_time(&localTime, "%Y-%m-%d");
    return ss.str();
}
