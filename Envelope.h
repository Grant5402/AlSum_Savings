#pragma once
#include <string>
#include <algorithm>
#include <cctype>

class Envelope
{
public:
	Envelope();

	Envelope(const std::string& name, double starting_balance, double starting_goal);

	std::string getIDName() const;

	std::string getDisplayName() const;

	double getBalance() const;

	double getGoal() const;

	bool inDebt();

	void addFunds(double amount);

	bool deductFunds(double amount);

private:
	std::string idName;
	std::string displayName;
	double balance;
	double goal;

	std::string toLowerCase(const std::string& input);
};

