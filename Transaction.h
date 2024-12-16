#pragma once
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

enum TransactionType {
    EXPENSE,
    INCOME,
    NONE
};

class Transaction
{
public:
    // Constructor
    Transaction();

    Transaction(int id, const std::string& desc, TransactionType t, double amt, const std::string& env, 
        const std::chrono::system_clock::time_point& date);

    Transaction(int id, const std::string& desc, TransactionType t, double amt, const std::string& env, 
        const std::chrono::system_clock::time_point& date,std::string source);

    // Getters
    int getId() const;
    std::string getDescription() const;
    std::string getEnvelope() const;
    TransactionType getType() const;
    double getAmount() const;
    std::string getSource() const;
    std::chrono::system_clock::time_point getDate() const;

    std::string getDateAsString() const; // For CSV saving
    void setDateFromString(const std::string& dateStr); // For CSV loading
    static std::chrono::system_clock::time_point parseDate(const std::string& dateStr);

private:
    int ID;                   // ID for tracking transaction
    std::string description;  // Description of the transaction (e.g., "Grocery Shopping")
    std::string source;       // Source of depost or withdraw (e.g., I got gass from caseys so I would list caseys) 
                              //    The goal is posisbly add panel for money spent at orgization break down
    std::string envelope;     // Envelope associated with the transaction
    TransactionType type;     // Type of transaction: expense, income, or ??
    double amount;            // Amount of the transaction
    std::chrono::system_clock::time_point date;

    std::string formatDate(const std::chrono::system_clock::time_point& tp) const;
};

