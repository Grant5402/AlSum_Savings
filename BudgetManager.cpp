#include "BudgetManager.h"

// Constructor: Initializes BudgetManager and loads envelopes and transactions from files
BudgetManager::BudgetManager(const std::string& filename)
{
    std::cout << "Initializing BudgetManager...\n";
    this->loadEnvelopes("envelopeData.csv");
    this->loadTransactions("transactionData.csv");
}

// Converts a string to lowercase for uniform key matching
std::string BudgetManager::toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
        });
    return result;
}

// +--------------------------------------------------------------------+
// |                        Envelope Management                         |
// +--------------------------------------------------------------------+

// Adds a new envelope with a unique name, starting balance, and goal amount
void BudgetManager::addEnvelope(const std::string& name, double initialBalance, double goal) {
    DebugPrint("Attempting to add envelope: " + name + "\n");

    // Check if the envelope name already exists (case-insensitive)
    if (envelopes.find(toLowerCase(name)) != envelopes.end()) {
        std::cout << "Envelope already exists: " << name << "\n";
        return;
    }

    // Add a new envelope to the map
    envelopes[toLowerCase(name)] = Envelope(name, initialBalance, goal);
    DebugPrint("Envelope added successfully: " + name + "\n");
}

// Removes an envelope and all its associated transactions
void BudgetManager::removeEnvelope(const std::string& name) {
    std::string lowerName = toLowerCase(name);

    // Check if the envelope exists and remove it
    if (envelopes.erase(lowerName)) {
        removeTransactionsForEnvelope(lowerName); // Remove all related transactions
        std::cout << "Envelope deleted: " << name << "\n";
    }
    else {
        std::cout << "Envelope not found: " << name << "\n";
    }
}

// Retrieves a reference to an existing envelope
// Throws an exception if the envelope does not exist
Envelope& BudgetManager::getEnvelope(const std::string& name) {
    auto it = envelopes.find(toLowerCase(name));
    if (it == envelopes.end()) {
        throw std::runtime_error("Envelope not found: " + name);
    }
    return it->second;
}

// Returns all envelopes in the system
std::unordered_map<std::string, Envelope> BudgetManager::getAllEnvelopes() {
    return envelopes;
}

// Saves all envelopes to a CSV file
void BudgetManager::saveEnvelopes(const std::string& filename) {
    std::ofstream file(filename);

    // Iterate through each envelope and save its data to the file
    for (const auto& env : envelopes) {
        file << env.second.getIDName() << ","
            << env.second.getDisplayName() << ","
            << env.second.getBalance() << ","
            << env.second.getGoal() << "\n";
    }
    file.close();
}

// Loads envelopes from a CSV file
void BudgetManager::loadEnvelopes(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, displayName, goalStr, balanceStr;

        // Parse each field in the line
        getline(ss, name, ',');
        getline(ss, displayName, ',');
        getline(ss, balanceStr, ',');
        getline(ss, goalStr, ',');

        // Add the envelope to the system
        addEnvelope(displayName, std::stod(balanceStr), std::stod(goalStr));
    }
    file.close();
}

// +--------------------------------------------------------------------+
// |                       Transaction Management                       |
// +--------------------------------------------------------------------+

// Adds a transaction without a source field
void BudgetManager::addTransaction(const std::string& desc, TransactionType t, double amt,
    const std::string& env, const std::string& date) {
    addTransaction(desc, t, amt, env, date, ""); // Overloaded method with empty source
}

// Adds a transaction with all details, including source
void BudgetManager::addTransaction(const std::string& desc, TransactionType t, double amt,
    const std::string& env, const std::string& date, std::string source) {
    // Update the envelope balance based on transaction type
    if (t == TransactionType::INCOME) {
        getEnvelope(env).addFunds(amt);
    }
    else if (t == TransactionType::EXPENSE) {
        getEnvelope(env).deductFunds(amt);
    }

    // Create and store the transaction
    transactions[transactionCounter] = Transaction(transactionCounter, desc, t, amt, env, parseDateString(date), source);

    // Update indexes for quick access
    envelopeIndexTransactions[toLowerCase(env)].push_back(transactionCounter);
    envelopeIndexDate.emplace(date, transactionCounter);

    transactionCounter++; // Increment the transaction ID counter

    saveTransactions("transactionData.csv"); // Save updated transactions
}

// Retrieves all transactions for a specific envelope
std::vector<Transaction> BudgetManager::getTransactionsForEnvelope(std::string env) {
    std::vector<Transaction> result;
    auto it = envelopeIndexTransactions.find(toLowerCase(env));

    // Check if there are any transactions for the envelope
    if (it != envelopeIndexTransactions.end()) {
        for (const int id : it->second) {
            result.push_back(transactions.at(id)); // Add transaction to the result list
        }
    }
    return result;
}

// Removes a specific transaction by its ID and adjusts the envelope balance
void BudgetManager::removeTransaction(int transactionId) {
    auto it = transactions.find(transactionId);
    if (it != transactions.end()) {
        Transaction transaction = it->second;

        // Adjust the envelope balance based on transaction type
        std::string envelopeName = toLowerCase(transaction.getEnvelope());
        if (envelopes.find(envelopeName) != envelopes.end()) {
            if (transaction.getType() == TransactionType::EXPENSE) {
                envelopes[envelopeName].addFunds(transaction.getAmount());
            }
            else if (transaction.getType() == TransactionType::INCOME) {
                envelopes[envelopeName].deductFunds(transaction.getAmount());
            }
        }

        // Remove transaction from indexes
        auto& transactionList = envelopeIndexTransactions[envelopeName];
        transactionList.erase(std::remove(transactionList.begin(), transactionList.end(), transactionId),
            transactionList.end());

        // Remove the transaction itself
        transactions.erase(it);
    }
    else {
        throw std::runtime_error("Transaction ID not found.");
    }
}

// Removes all transactions for a specific envelope
void BudgetManager::removeTransactionsForEnvelope(const std::string& envelopeName) {
    auto it = envelopeIndexTransactions.find(toLowerCase(envelopeName));

    // If transactions exist, remove them
    if (it != envelopeIndexTransactions.end()) {
        for (int id : it->second) {
            transactions.erase(id);
        }
        envelopeIndexTransactions.erase(it);
    }
}

// Saves all transactions to a CSV file
void BudgetManager::saveTransactions(const std::string& filename) {
    std::ofstream file(filename);

    for (const auto& transaction : transactions) {
        file << transaction.second.getId() << ","
            << transaction.second.getDescription() << ","
            << transaction.second.getType() << ","
            << transaction.second.getAmount() << ","
            << transaction.second.getEnvelope() << ","
            << transaction.second.getDateAsString() << ","
            << transaction.second.getSource() << "\n";
    }
    file.close();
}

// Loads transactions from a CSV file
void BudgetManager::loadTransactions(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, desc, envName, amountStr, typeStr, dateStr, source;

        // Parse transaction details
        getline(ss, idStr, ',');
        getline(ss, desc, ',');
        getline(ss, typeStr, ',');
        getline(ss, amountStr, ',');
        getline(ss, envName, ',');
        getline(ss, dateStr, ',');
        getline(ss, source, ',');

        // Convert and add the transaction
        TransactionType type = static_cast<TransactionType>(std::stoi(typeStr));
        transactions[transactionCounter] = Transaction(transactionCounter, desc, type, std::stod(amountStr), envName,
            parseDateString(dateStr), source);

        envelopeIndexTransactions[toLowerCase(envName)].push_back(transactionCounter);
        envelopeIndexDate.emplace(dateStr, transactionCounter);

        transactionCounter++;
    }
    file.close();
}

// Helper method to parse a date string (e.g., "2024-06-18") into a time_point
std::chrono::system_clock::time_point BudgetManager::parseDateString(const std::string& dateStr) {
    std::istringstream ss(dateStr);
    std::tm tm = {};
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

// Outputs debug messages to the debug console
void BudgetManager::DebugPrint(const std::string& message) {
    OutputDebugStringA(message.c_str());
}
