#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include <ctime>
#include <chrono>
#include <iomanip>

#include <windows.h>

#include "Envelope.h"
#include "Transaction.h"

// Class responsible for managing envelopes and transactions in the budgeting system
class BudgetManager
{
public:
    // Constructor: initializes BudgetManager and loads data from files
    BudgetManager(const std::string& filename);

    // +--------------------------------------------------------------------+
    // |                        Envelope Management                         |
    // +--------------------------------------------------------------------+

    void addEnvelope(const std::string& name, double initialBalance, double goal);
    // Adds a new envelope to the system with a given name, starting balance, and goal.

    void removeEnvelope(const std::string& name);
    // Removes an envelope and its associated transactions.

    Envelope& getEnvelope(const std::string& name);
    // Retrieves a reference to a specific envelope by its name.

    std::unordered_map<std::string, Envelope> getAllEnvelopes();
    // Returns all envelopes in the system as an unordered map.

    void saveEnvelopes(const std::string& filename);
    // Saves all envelopes to a specified CSV file.

    void loadEnvelopes(const std::string& filename);
    // Loads envelopes from a specified CSV file.

    // +--------------------------------------------------------------------+
    // |                       Transaction Management                       |
    // +--------------------------------------------------------------------+

    void addTransaction(const std::string& desc, TransactionType t, double amt,
        const std::string& env, const std::string& date);
    // Adds a transaction without a source field.

    void addTransaction(const std::string& desc, TransactionType t, double amt,
        const std::string& env, const std::string& date, std::string source);
    // Adds a transaction with all details, including the source.

    std::vector<Transaction> getTransactionsForEnvelope(std::string env);
    // Retrieves all transactions associated with a specific envelope.

    void removeTransaction(int transactionId);
    // Removes a specific transaction by its ID and adjusts the envelope balance.

    void removeTransactionsForEnvelope(const std::string& envelopeName);
    // Removes all transactions for a specific envelope.

    void transferTransaction(int id, std::string& env);
    // Placeholder: Transfers a transaction to a different envelope.

    void saveTransactions(const std::string& filename);
    // Saves all transactions to a specified CSV file.

    void loadTransactions(const std::string& filename);
    // Loads transactions from a specified CSV file.

    void DebugPrint(const std::string& message);
    // Outputs debug messages to the debug console.

private:
    int transactionCounter = 0; // Counter to assign unique transaction IDs
    std::string filename;       // Filepath used for saving/loading data

    std::unordered_map<std::string, Envelope> envelopes; // Stores all envelopes
    std::unordered_map<int, Transaction> transactions;   // Stores all transactions

    // Indexes for quick access
    std::unordered_map<std::string, std::vector<int>> envelopeIndexTransactions; // Maps envelope names to transaction IDs
    std::multimap<std::string, std::vector<int>> envelopeIndexDate;              // Maps dates to transaction IDs

    std::string toLowerCase(const std::string& input); // Helper function to convert a string to lowercase
    std::chrono::system_clock::time_point parseDateString(const std::string& dateStr);
    // Parses a date string into a system clock time point
};
