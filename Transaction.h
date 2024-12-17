#pragma once
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

// Enum representing the type of transaction: Expense, Income, or None
enum TransactionType {
    EXPENSE,  // Deducts funds
    INCOME,   // Adds funds
    NONE      // Default or uninitialized type
};

// Class representing a single transaction in the budget system
class Transaction
{
public:
    // Default constructor: initializes a blank transaction
    Transaction();

    // Constructor with essential transaction details (no source field)
    Transaction(int id, const std::string& desc, TransactionType t, double amt, const std::string& env,
        const std::chrono::system_clock::time_point& date);

    // Constructor with all transaction details including source
    Transaction(int id, const std::string& desc, TransactionType t, double amt, const std::string& env,
        const std::chrono::system_clock::time_point& date, std::string source);

    // Getters
    int getId() const;                       // Returns the transaction ID
    std::string getDescription() const;      // Returns the transaction description
    std::string getEnvelope() const;         // Returns the associated envelope name
    TransactionType getType() const;         // Returns the transaction type
    double getAmount() const;                // Returns the transaction amount
    std::string getSource() const;           // Returns the source of the transaction
    std::chrono::system_clock::time_point getDate() const; // Returns the transaction date

    std::string getDateAsString() const;     // Returns the date as a formatted string (e.g., "YYYY-MM-DD")
    void setDateFromString(const std::string& dateStr); // Parses and sets the date from a string

    // Static helper to parse a date string into a time_point
    static std::chrono::system_clock::time_point parseDate(const std::string& dateStr);

private:
    int ID;                       // Unique identifier for the transaction
    std::string description;      // Description of the transaction (e.g., "Grocery Shopping")
    std::string source;           // Source of transaction (e.g., store name, employer)
    std::string envelope;         // Associated envelope name
    TransactionType type;         // Type of transaction: Expense, Income, or None
    double amount;                // Amount of the transaction
    std::chrono::system_clock::time_point date; // Date of the transaction

    // Helper function to format a time_point as a string
    std::string formatDate(const std::chrono::system_clock::time_point& tp) const;
};
