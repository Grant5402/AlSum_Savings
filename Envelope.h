#pragma once
#include <string>
#include <algorithm>
#include <cctype>

// Class representing an individual "envelope" for budgeting
class Envelope
{
public:
    // Constructors
    Envelope();
    Envelope(const std::string& name, double starting_balance, double starting_goal);

    // Accessor methods (getters)
    std::string getIDName() const;        // Returns the internal lowercase ID name
    std::string getDisplayName() const;   // Returns the display name
    double getBalance() const;            // Returns the current balance
    double getGoal() const;               // Returns the goal amount

    // Utility methods
    bool inDebt();                        // Checks if the envelope is in debt
    void addFunds(double amount);         // Adds funds to the envelope
    bool deductFunds(double amount);      // Deducts funds and returns if balance is non-negative

private:
    // Member variables
    std::string idName;      // Internal lowercase ID name
    std::string displayName; // Display name
    double balance;          // Current balance
    double goal;             // Goal amount

    // Helper method to convert a string to lowercase
    std::string toLowerCase(const std::string& input);
};
