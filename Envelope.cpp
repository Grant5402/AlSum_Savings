#include "Envelope.h"

// Default constructor initializes an envelope with placeholder values
Envelope::Envelope()
{
    idName = "blank";       // Internal ID name (lowercase)
    displayName = "blank";  // Display name for the envelope
    balance = 0;            // Starting balance
    goal = 0;               // Goal amount for the envelope
}

// Parameterized constructor initializes an envelope with provided name, balance, and goal
Envelope::Envelope(const std::string& name, double starting_balance, double starting_goal) {
    idName = Envelope::toLowerCase(name);  // Convert the name to lowercase for consistency
    displayName = name;                    // Retain the display name as entered
    balance = starting_balance;            // Set starting balance
    goal = starting_goal;                  // Set goal amount
}

// Returns the ID name of the envelope (internal use)
std::string Envelope::getIDName() const
{
    return idName;  // Should return the lowercase ID name
}

// Returns the display name of the envelope
std::string Envelope::getDisplayName() const {
    return displayName;
}

// Returns the current balance of the envelope
double Envelope::getBalance() const {
    return balance;
}

// Returns the goal amount of the envelope
double Envelope::getGoal() const {
    return goal;
}

// Checks if the envelope balance is zero or less (indicating debt)
bool Envelope::inDebt() {
    return balance <= 0;
}

// Adds funds to the envelope balance
void Envelope::addFunds(double amount) {
    balance += amount;
}

// Deducts funds from the envelope balance
// Returns true if balance remains non-negative after deduction, false otherwise
bool Envelope::deductFunds(double amount) {
    balance -= amount;
    return balance >= 0;  // Return whether the balance is still non-negative
}

// Converts a string to lowercase for uniformity (helper function)
std::string Envelope::toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);  // Convert each character to lowercase
        });
    return result;
}
